# Graph Report - .  (2026-06-12)

## Corpus Check
- Corpus is ~19,360 words - fits in a single context window. You may not need a graph.

## Summary
- 363 nodes · 616 edges · 34 communities (30 shown, 4 thin omitted)
- Extraction: 72% EXTRACTED · 28% INFERRED · 0% AMBIGUOUS · INFERRED: 174 edges (avg confidence: 0.8)
- Token cost: 1,200 input · 900 output

## Community Hubs (Navigation)
- [[_COMMUNITY_Env Unset and Expander Core|Env Unset and Expander Core]]
- [[_COMMUNITY_Path Expansion and Command Lookup|Path Expansion and Command Lookup]]
- [[_COMMUNITY_Libft Utils and AST Helpers|Libft Utils and AST Helpers]]
- [[_COMMUNITY_Env Builtin and Debug Printer|Env Builtin and Debug Printer]]
- [[_COMMUNITY_Builtin Dispatch (cd, export, exit)|Builtin Dispatch (cd, export, exit)]]
- [[_COMMUNITY_Minishell Architecture Overview|Minishell Architecture Overview]]
- [[_COMMUNITY_Echo and Export Builtins|Echo and Export Builtins]]
- [[_COMMUNITY_Lexer and Tokenizer|Lexer and Tokenizer]]
- [[_COMMUNITY_Printf Dispatch and Conversion|Printf Dispatch and Conversion]]
- [[_COMMUNITY_Linked List Operations|Linked List Operations]]
- [[_COMMUNITY_AST Executor (pipe, and, or)|AST Executor (pipe, and, or)]]
- [[_COMMUNITY_GNL and Buffer Management|GNL and Buffer Management]]
- [[_COMMUNITY_Heredoc Processing|Heredoc Processing]]
- [[_COMMUNITY_Exit and Cleanup|Exit and Cleanup]]
- [[_COMMUNITY_List Front Insert|List Front Insert]]
- [[_COMMUNITY_List Node Delete|List Node Delete]]
- [[_COMMUNITY_List Iterator|List Iterator]]
- [[_COMMUNITY_List Size|List Size]]

## God Nodes (most connected - your core abstractions)
1. `ft_strlen()` - 21 edges
2. `Minishell Project` - 19 edges
3. `exec_builtin()` - 13 edges
4. `_process_input()` - 12 edges
5. `build_subshell()` - 12 edges
6. `ft_printf()` - 11 edges
7. `exec_ast()` - 11 edges
8. `ft_strdup()` - 10 edges
9. `ft_substr()` - 10 edges
10. `ft_strncmp()` - 9 edges

## Surprising Connections (you probably didn't know these)
- `_check_key()` --calls--> `ft_isalnum()`  [INFERRED]
  srcs/builtins/export.c → libs/libft/srcs/libc/ft_isalnum.c
- `_check_key()` --calls--> `ft_isalpha()`  [INFERRED]
  srcs/builtins/export.c → libs/libft/srcs/libc/ft_isalpha.c
- `get_env_var()` --calls--> `ft_itoa()`  [INFERRED]
  srcs/expander/expander_var_utils.c → libs/libft/srcs/libc/ft_itoa.c
- `_exapand_heredoc_line()` --calls--> `ft_memcpy()`  [INFERRED]
  srcs/parser/heredoc.c → libs/libft/srcs/libc/ft_memcpy.c
- `handle_operator()` --calls--> `ft_putstr_fd()`  [INFERRED]
  srcs/lexer/lexer_handling.c → libs/libft/srcs/libc/ft_putstr_fd.c

## Import Cycles
- None detected.

## Hyperedges (group relationships)
- **Shell Lifecycle (prompt, parse, execute)** — readme_lexer, readme_parser, readme_executor, readme_minishell_project [EXTRACTED 1.00]
- **I/O Control Features (redirections, pipes, heredoc)** — readme_redirections, readme_pipes, readme_heredoc [EXTRACTED 1.00]
- **Core Shell Feature Set** — readme_builtins, readme_env_expansion, readme_quote_parsing, readme_signals, readme_readline [INFERRED 0.95]

## Communities (34 total, 4 thin omitted)

### Community 0 - "Env Unset and Expander Core"
Cohesion: 0.07
Nodes (18): execute_unset(), expand_token_list(), _expand_with_path(), _expand_with_quotes(), _append_var(), expand_loop(), _expand_one_var(), _in_quote_switcher() (+10 more)

### Community 1 - "Path Expansion and Command Lookup"
Cohesion: 0.09
Nodes (27): get_cmd_path(), _get_env_path(), expand_path(), grab_filenames(), match_pattern(), update_token(), count_dir_entries(), count_matches() (+19 more)

### Community 2 - "Libft Utils and AST Helpers"
Cohesion: 0.11
Nodes (28): ft_bzero(), ft_calloc(), ft_putstr_fd(), ast_new_cmd_node(), ast_new_op(), find_logical_op(), find_pipe_op(), print_syntax_error() (+20 more)

### Community 3 - "Env Builtin and Debug Printer"
Cohesion: 0.10
Nodes (25): execute_env(), print_cmd_node(), _print_redir(), _parse_print_ast(), print_ast(), print_env_list(), print_tok_list(), ft_printf() (+17 more)

### Community 4 - "Builtin Dispatch (cd, export, exit)"
Cohesion: 0.14
Nodes (19): _change_dir(), execute_cd(), _throw_error(), exec_builtin(), dispatch_cmd(), _exec_parent_builtin(), execute_child(), _is_builtin() (+11 more)

### Community 5 - "Minishell Architecture Overview"
Cohesion: 0.10
Nodes (24): 42 School Curriculum, Bash Shell, Built-in Commands, Environment Variable Expansion, Executor Module, Expander Module, Unofficial Shell Documentation (Grymoire), Heredoc (<<) (+16 more)

### Community 6 - "Echo and Export Builtins"
Cohesion: 0.11
Nodes (15): execute_echo(), _is_flag(), _check_key(), execute_export(), _export_list(), _export_one_var(), _throw_error(), execute_pwd() (+7 more)

### Community 7 - "Lexer and Tokenizer"
Cohesion: 0.21
Nodes (19): _extract_word(), _append_op(), _handle_double_op(), handle_operator(), handle_quotes(), lexer(), _process_character(), free_tok_ls() (+11 more)

### Community 8 - "Printf Dispatch and Conversion"
Cohesion: 0.22
Nodes (16): convert_char(), convert_num(), convert_str(), dispatch_conversion(), pf_itoa(), pf_uitoa(), str0(), pf_strlen() (+8 more)

### Community 9 - "Linked List Operations"
Cohesion: 0.13
Nodes (10): ft_lstadd_back(), ft_lstclear(), ft_lstlast(), ft_lstmap(), ft_lstnew(), t_list, t_list, t_list (+2 more)

### Community 10 - "AST Executor (pipe, and, or)"
Cohesion: 0.37
Nodes (11): exec_and(), exec_ast(), exec_or(), exec_subshell(), _exec_left_child(), exec_pipe(), _exec_right_child(), t_ast_node (+3 more)

### Community 11 - "GNL and Buffer Management"
Cohesion: 0.26
Nodes (9): ft_realloc(), ensure_capacity(), extract_line(), get_next_line(), init_stash_buffers(), read_loop(), ft_memcpy(), ft_memmove() (+1 more)

### Community 12 - "Heredoc Processing"
Cohesion: 0.29
Nodes (10): charactercounter(), ft_itoa(), _exapand_heredoc_line(), _fill_heredoc(), _generate_tmp_filename(), process_all_heredocs(), _process_single_heredoc(), t_ast_node (+2 more)

### Community 13 - "Exit and Cleanup"
Cohesion: 0.24
Nodes (9): execute_exit(), _clean_ast(), _clean_env(), _clean_envp(), clean_ms(), t_minishell, t_ast_node, t_env (+1 more)

## Knowledge Gaps
- **43 isolated node(s):** `t_list`, `t_list`, `t_list`, `t_list`, `t_list` (+38 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **4 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `ft_strlen()` connect `Echo and Export Builtins` to `Env Unset and Expander Core`, `Path Expansion and Command Lookup`, `Libft Utils and AST Helpers`, `Builtin Dispatch (cd, export, exit)`, `GNL and Buffer Management`, `Heredoc Processing`, `Exit and Cleanup`?**
  _High betweenness centrality (0.129) - this node is a cross-community bridge._
- **Why does `ft_printf()` connect `Env Builtin and Debug Printer` to `Printf Dispatch and Conversion`, `Exit and Cleanup`, `Echo and Export Builtins`?**
  _High betweenness centrality (0.097) - this node is a cross-community bridge._
- **Why does `dispatch_conversion()` connect `Printf Dispatch and Conversion` to `Env Builtin and Debug Printer`?**
  _High betweenness centrality (0.052) - this node is a cross-community bridge._
- **Are the 20 inferred relationships involving `ft_strlen()` (e.g. with `execute_cd()` and `execute_echo()`) actually correct?**
  _`ft_strlen()` has 20 INFERRED edges - model-reasoned connections that need verification._
- **Are the 10 inferred relationships involving `exec_builtin()` (e.g. with `execute_cd()` and `execute_echo()`) actually correct?**
  _`exec_builtin()` has 10 INFERRED edges - model-reasoned connections that need verification._
- **Are the 8 inferred relationships involving `_process_input()` (e.g. with `print_ast()` and `exec_ast()`) actually correct?**
  _`_process_input()` has 8 INFERRED edges - model-reasoned connections that need verification._
- **Are the 7 inferred relationships involving `build_subshell()` (e.g. with `build_ast()` and `free_tok_ls()`) actually correct?**
  _`build_subshell()` has 7 INFERRED edges - model-reasoned connections that need verification._