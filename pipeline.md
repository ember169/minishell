# Minishell — String Processing Pipeline

> Tracing `env | grep $USER` from raw user input to execution.

---

## Overview

| Stage | Input | Output | Key Structure |
|-------|-------|--------|---------------|
| **1. Input** | keystrokes | `char *` raw string | — |
| **2. Lexer** | `"env \| grep $USER"` | token linked list (`$USER` raw) | `t_token` |
| **3. Expander** | token list with `"$USER"` | token list with `"mskn"` | `t_token` (mutated) |
| **4. Parser** | flat token list | binary AST | `t_ast_node` |
| **5. Executor** | AST tree | processes + pipe + execve | OS fd table |

---

## Stage 1 — User Input

**File:** `srcs/main.c`

```
readline(PROMPT)
    │
    ▼
char *uinput = "env | grep $USER"    ← raw heap-allocated string
    │
    ├── add_to_history(uinput)        saved to readline history
    └── _process_input(ms, uinput)
```

`_process_input()` (`main.c:80`) orchestrates every subsequent stage in sequence:
lexer → expander → parser → heredoc → executor → cleanup.

---

## Stage 2 — Lexer

**Files:** `srcs/lexer/lexer.c`, `lexer_handling.c`, `lexer_utils.c`  
**Entry point:** `lexer(char *input)` → `lexer.c:74`

The lexer walks the input string character by character using a two-state machine
(`t_lexer_state { state=GENERAL|IN_QUOTE, i }`). Each character is dispatched by
`_process_character()`:

| Input chars | Condition | Handler | Token emitted |
|-------------|-----------|---------|---------------|
| `env` | not quote, not operator | `_extract_word()` → `ft_substr()` | `TOK_WORD "env"` |
| ` ` | `is_space()` | `ls->i++` (skip) | — |
| `\|` | `is_operator()` | `handle_operator()` → `_append_op()` | `TOK_PIPE` |
| ` ` | space | skip | — |
| `grep` | word | `_extract_word()` | `TOK_WORD "grep"` |
| ` ` | space | skip | — |
| `$USER` | word (`$` is not an operator) | `_extract_word()` | `TOK_WORD "$USER"` |

> **`$USER` is not expanded here.** The lexer treats `$` as a regular word character.
> Quote tokens (`'…'`, `"…"`) are extracted including their delimiters by `handle_quotes()`,
> which uses the state machine to skip past the closing quote.

**Output — `t_token` linked list:**

```
[TOK_WORD:"env"] → [TOK_PIPE:NULL] → [TOK_WORD:"grep"] → [TOK_WORD:"$USER"] → NULL
```

---

## Stage 3 — Expander

**Files:** `srcs/expander/expander.c`, `expander_quote_expand.c`, `expander_var_utils.c`, `expander_path_expand.c`  
**Entry point:** `expand_token_list(ms, list)` → `expander.c:53`  
**Called via:** `_format_tokens(ms, list)` in `main.c:89`

For every `TOK_WORD` token:

**① `"env"` and `"grep"` — no `$`, no `*`**
- `_expand_with_quotes(ms, str)` → `expand_loop()` copies chars as-is → unchanged.
- `_expand_with_path()` → no `*` → no glob expansion.

**② `"$USER"` — variable expansion**

```
_expand_with_quotes(ms, "$USER")
  └── expand_loop()                          expander_quote_expand.c:92
        src="$USER", in_quote='\0'
        *src == '$' && in_quote != '\''
          └── _expand_one_var(ms, &src, &dst)
                get_key_len("$USER")         → 4  (scans alnum + '_')
                get_env_var(ms, "$USER", &var):
                  ft_substr("$USER", 1, 4)   → key = "USER"
                  get_env_addr_from_key(ms, "USER")  → t_env node
                  ft_strdup(env->value)       → var = "mskn"
                _append_var(dst, "mskn")      → write into output buffer
                src += 1 + 4                  → advance past "$USER"
        *dst = '\0'
        return "mskn"
```

`token->value` (`"$USER"`) is `free()`d and replaced with `"mskn"`.

**Quote protection rule:** inside single quotes, `$` is never expanded.
`expand_loop()` checks `in_quote != '\''` before calling `_expand_one_var()`.
So `grep '$USER'` would pass `$USER` literally to grep.

**Output — same list structure, values updated:**

```
[TOK_WORD:"env"] → [TOK_PIPE:NULL] → [TOK_WORD:"grep"] → [TOK_WORD:"mskn"] → NULL
```

---

## Stage 4 — Parser / AST Builder

**Files:** `srcs/parser/build_ast.c`, `ast_utils.c`, `handle_redir.c`  
**Entry point:** `build_ast(t_token *tok)` → `build_ast.c:100`

`build_ast()` is recursive and builds the tree top-down by operator precedence
(logical ops first, then pipes, then commands):

```
build_ast([env] → [|] → [grep] → [mskn])
  │
  ├── find_logical_op()  → no && or ||  → NULL
  ├── find_pipe_op()     → finds TOK_PIPE  → split_pts
  └── _split_ast_op(tok, split_pts):
        node_type = NODE_PIPE
        right_tok = split_pts->next       → [grep] → [mskn]
        sever list: current->next = NULL  → left is now [env]
        │
        ├── left_ast  = build_ast([env])
        │     find_logical_op → NULL
        │     find_pipe_op    → NULL
        │     _parse_cmd([env]):
        │       ast_new_cmd_node()        → malloc t_ast_node (NODE_CMD)
        │       _count_args()             → 1
        │       malloc(char* × 2)         → args array
        │       _fill_cmd_args():
        │         args[0] = ft_strdup("env")
        │         args[1] = NULL
        │
        └── right_ast = build_ast([grep] → [mskn])
              _parse_cmd([grep] → [mskn]):
                args[0] = "grep"
                args[1] = "mskn"
                args[2] = NULL
        
        ast_new_op(NODE_PIPE, left_ast, right_ast)
```

> `find_pipe_op()` always stores `last_found`, making pipes **left-associative**:
> `a | b | c` parses as `(a | b) | c`.

**Output — `t_ast_node` binary tree:**

```
              ┌───────────────┐
              │   NODE_PIPE   │
              └───┬───────┬───┘
                  │       │
       ┌──────────▼──┐  ┌─▼────────────────┐
       │  NODE_CMD   │  │     NODE_CMD      │
       │ args:       │  │ args:             │
       │ ["env",NULL]│  │ ["grep","mskn",   │
       │ redirs: NULL│  │  NULL]            │
       └─────────────┘  │ redirs: NULL      │
                        └───────────────────┘
```

---

## Stage 5 — Executor

**Files:** `srcs/executor/exec_ast.c`, `exec_pipe.c`, `exec_dispatcher.c`, `exec_path.c`, `redirections.c`  
**Entry point:** `exec_ast(ms, ms->ast_root)` → `exec_ast.c:56`

Before execution: `generate_envp_array(ms->env_list)` builds the `char **envp` array
needed by `execve()`.

### exec_ast dispatch

```
exec_ast(ms, NODE_PIPE)
  node->type == NODE_PIPE  →  exec_pipe(ms, node)
```

### exec_pipe — pipe + two forks

```
exec_pipe(ms, node)                          exec_pipe.c:31
  │
  ├── pipe(pfd)         pfd[0]=read end, pfd[1]=write end
  │
  ├── fork() → pid_left
  │   └── CHILD LEFT: _exec_left_child()
  │         close(pfd[0])               discard read end
  │         dup2(pfd[1], STDOUT_FILENO) stdout → pipe write end
  │         close(pfd[1])
  │         exec_ast(ms, NODE_CMD["env"])
  │           dispatch_cmd(ms, node)
  │             _is_env_unsafe("env")  → false  → fork()
  │               execute_child():
  │                 setup_redirections() → no redirs → noop
  │                 _is_builtin("env")  → TRUE
  │                 exec_builtin(ms, node)  ← writes all env vars to stdout
  │                 stdout == pipe write end  →  data flows into pipe
  │                 exit(0)
  │
  ├── fork() → pid_right
  │   └── CHILD RIGHT: _exec_right_child()
  │         close(pfd[1])               discard write end
  │         dup2(pfd[0], STDIN_FILENO)  stdin ← pipe read end
  │         close(pfd[0])
  │         exec_ast(ms, NODE_CMD["grep","mskn"])
  │           dispatch_cmd(ms, node)
  │             _is_env_unsafe("grep") → false → fork()
  │               execute_child():
  │                 setup_redirections() → noop
  │                 _is_builtin("grep") → FALSE
  │                 get_cmd_path(ms, "grep") → "/usr/bin/grep"
  │                 execve("/usr/bin/grep", ["grep","mskn",NULL], ms->envp)
  │                 stdin == pipe read end  →  reads env output, filters by "mskn"
  │
  └── PARENT:
        close(pfd[0]), close(pfd[1])
        waitpid(pid_left,  NULL,    0)
        waitpid(pid_right, &status, 0)
        ms->last_status = WEXITSTATUS(status)   ← grep's exit code
```

### Why `env` runs in a fork despite being a builtin

`_is_env_unsafe()` only covers `cd`, `export`, `unset`, `exit` — commands that
must mutate the shell's own environment. `env`, `echo`, and `pwd` go through the
normal `fork()` path in `dispatch_cmd()`, so their output can be safely redirected
(here, into the pipe).

---

## Stage 6 — Cleanup

**File:** `srcs/main.c`

```
free_str_array(ms->envp)    envp char** array freed
free_ast(ms->ast_root)      entire AST tree recursively freed
ms->ast_root = NULL
→ back to readline() for next input
```

---

## Design Notes

- **Expansion before parsing** — `expand_token_list()` runs on the flat token list
  before `build_ast()` is ever called. The parser only ever sees already-expanded values.

- **Single quotes protect `$`** — `expand_loop()` (`expander_quote_expand.c:105`)
  checks `in_quote != '\''` before expanding. `grep '$USER'` passes `$USER` to grep literally.

- **Operator tokens carry no `value`** — `TOK_PIPE`, `TOK_AND`, etc. are created with
  `token_new(NULL, type)`. Only `TOK_WORD` tokens carry a string.

- **Left-associative pipes** — `find_pipe_op()` always updates `last_found` while
  scanning, so the rightmost pipe is the split point, building a left-leaning tree.
