*This project has been created as part of the 42 curriculum by lgervet and achavier*
# minishell
C minimal command interpreter

## Description
This project involves creating a simplified shell, modeled after Bash. You will develop a command-line interpreter that handles the basic lifecycle of a terminal: displaying a prompt, parsing user input, and executing commands while managing system resources and processes

### Prerequisites
#### Technical Requirements
- **The Prompt:** Display a prompt while waiting for a new command.
- **The History:** Maintain a functional command history.
- **Execution:** Find and launch the correct executables (via `PATH` or specific paths).
- **Signals:**
  - `Ctrl-C`: Displays a new prompt on a new line.
  - `Ctrl-D`: Exits the shell.
  - `Ctrl-\`: Does nothing.
- **Parsing:** 
  - Single Quotes: Prevent the shell from interpreting meta-characters.
  - Double Quotes: Prevent meta-characters interpretation except for `$` (expansion).

#### Features
- **Redirections:**
  - `<` : Redirect input.
  - `>` : Redirect output (overwrite).
  - `<<` : Read input until a delimiter is seen (heredoc).
  - `>>` : Redirect output (append).
- **Pipes:** Implement `|` to connect the output of one command to the input of the next.
- **Environment:** Expand environment variables (e.g., `$VAR`) and the exit status (`$?`).

#### Built-ins
The shell must implement the following commands internally:
- `echo` (with option `-n`)
- `cd` (relative or absolute path only)
- `pwd`, `export`, `unset`, `env`, `exit`

#### Allowed external functions:**
> `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

### Implementation
*Building...*

## Instructions
### Compiling
*Building...*

### Executing
*Building...*

## Resources

### Documentation
#### Concept & Theory
*Building...*

#### Learning Resources 
*Building...*

#### Technical Reference & Helpers
*Building...*

### AI Usage
*Building...*
