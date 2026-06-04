*This project has been created as part of the 42 curriculum by lgervet and achavier*
# minishell
C minimal command interpreter

## Description
This project involves creating a simplified shell, modeled after Bash. You will develop a command-line interpreter that handles the basic lifecycle of a terminal: displaying a prompt, parsing user input, and executing commands while managing system resources and processes

### Prerequisites
#### Technical Requirements
- The Prompt: Display a prompt while waiting for a new command.
- The History: Maintain a functional command history.
- Execution: Find and launch the correct executables (via `PATH` or specific paths).
- Signals:
  - `Ctrl-C`: Displays a new prompt on a new line.
  - `Ctrl-D`: Exits the shell.
  - `Ctrl-\`: Does nothing.
- Parsing: 
  - Single Quotes: Prevent the shell from interpreting meta-characters.
  - Double Quotes: Prevent meta-characters interpretation except for `$` (expansion).

#### Features
- Redirections:
  - `<` : Redirect input.
  - `>` : Redirect output (overwrite).
  - `<<` : Read input until a delimiter is seen (heredoc).
  - `>>` : Redirect output (append).
- Pipes: Implement `|` to connect the output of one command to the input of the next.
- Environment: Expand environment variables (e.g., `$VAR`) and the exit status (`$?`).

#### Built-ins
The shell must implement the following commands internally:
- `echo` (with option `-n`)
- `cd` (relative or absolute path only)
- `pwd`, `export`, `unset`, `env`, `exit`

#### Allowed external functions:
> `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

### Implementation

#### Naming Rules Summary

| Pattern | Use Case | Example |
| :--- | :--- | :--- |
| `module.c` | Main entry point(s) | `lexer.c` |
| `module_checkers.c` | Validation/checking functions | `init_checkers.c` |
| `module_creators.c` | Creation/init functions | `init_creators.c` |
| `module_operators.c` | Operator handling | `lexer_operators.c` |
| `module_tokens.c` | Token manipulation | `lexer_tokens.c` |
| `module_helpers.c` | General utilities for the module | `expander_helpers.c` |
| `module_vars.c` | Variable-specific logic | `expander_vars.c` |
Each file should have a clear, single responsibility matching its suffix

## Instructions
### Compiling
*Building...*

### Executing
*Building...*

## Resources

### Documentation
#### Concept & Theory
- [Third argument of main() for env variables, Stackoverflow, 2014](https://stackoverflow.com/questions/21939379/main-function-with-three-arguments)
- [How to make an elegant tokenizer in C, Zarial, 2020](https://ix-56h.github.io/how-to-make-a-tokenizer/)
	- Convinced me to make a simple implementation of a Reverse Descent Parser before beginning the project: [math_shell (github)](https://github.com/ember169/math_shell)
- [Parent and child of fork() in C, Stackoverflow, 2013](https://stackoverflow.com/questions/22007031/parent-and-child-of-fork-in-c)

#### Technical Reference & Helpers
- [Official POSIX Shell documentation, Opengroup, 2018](https://pubs.opengroup.org/onlinepubs/9699919799/)
- [Unofficial Shell documentation, Grymoire, 2023](https://www.grymoire.com/Unix/Sh.html)

### AI Usage
- To divide the entire project into seven Phases, making it easy for us to plan and keep track of the project while working simultaneously on different features.
- To make sense of some intricates concepts (i.e: Lexer, Tokenizer, Expander, Executor...)
- To conceive a robust nested structure architecture
- To 