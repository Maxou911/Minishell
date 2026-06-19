# Minishell

*This project has been created as part of the 42 curriculum by maalwis, uzyberaj*

## Description

Minishell is a simplified Unix shell implementation written in C.  
The goal of this project is to understand how a shell works internally by reproducing some of Bash's core features, including command execution, pipes, redirections, environment variables, and signal handling.

---

## Features

### Command Execution
- Execution of external commands
- Search for executables using the `PATH` environment variable
- Process creation using `fork()`
- Program execution using `execve()`
- Management of command exit statuses (`$?`)

### Builtins
- `echo` with the `-n` option
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### Redirections
- Input redirection: `<`
- Output redirection: `>`
- Append redirection: `>>`
- Here-document: `<<`

### Pipes
- Support for pipes (`|`)
- Execution of multiple commands connected through pipelines

### Environment Variables
- Expansion of environment variables (`$USER`, `$HOME`, etc.)
- Support for the special variable `$?`

### Quotes Handling
- Single quotes `'...'`
- Double quotes `"..."`

### Signals
- `Ctrl-C`: displays a new prompt, return code : 130
- `Ctrl-D`: exits the shell
- `Ctrl-\`: ignored in interactive mode, return code : 131r

---

## Compilation

Build the project:

```bash
make
```

Available rules:

```bash
make
make clean
make fclean
make re
```

---

## Usage

Start the shell:

```bash
./minishell
```

Examples:

```bash
minishell$ ls -la
minishell$ echo "Hello World"
minishell$ cat file.txt | grep test
minishell$ echo $HOME
minishell$ cat << EOF
```

---

## Concepts Covered

- Processes and `fork()`
- `execve()`
- File descriptors
- Pipes and redirections
- Environment variables
- Command-line parsing
- Signal handling
- Memory management in C

---
