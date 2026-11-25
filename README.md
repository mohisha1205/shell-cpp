# Shell Implementation in C++

A command-line shell implemented from scratch in **C++**.

The project explores how a Unix-like shell reads user input, interprets commands, executes programs, and interacts with the filesystem. It is being developed incrementally, with each feature implemented and tested as a separate stage.

## Features Implemented

### 1. Shell Fundamentals
- Interactive command-line prompt.
- Read-Eval-Print Loop (REPL) for continuously accepting and processing commands.
- Handling of invalid and unrecognized commands.
- Built-in commands:
  - `exit` – terminate the shell.
  - `echo` – print text to standard output.
  - `type` – identify whether a command is a shell builtin or an executable.

### 2. External Command Execution
- Locate executable files using the system's `PATH` environment variable.
- Execute external programs from the shell.
- Handle commands that cannot be found.

### 3. Directory Navigation
- `pwd` – display the current working directory.
- `cd` – change the current working directory.
  - Absolute paths.
  - Relative paths.
  - Home directory (`~`).

### 4. Command Parsing and Quoting
- Basic command parsing.
- Support for **single-quoted strings**, allowing text containing spaces to be interpreted as a single argument.
- Preserve the literal contents of single-quoted strings.

## Tech Stack

- **Language:** C++
- **Build System:** CMake
- **Concepts:** Operating Systems, REPLs, command parsing, process execution, environment variables, filesystem navigation.

## Building and Running

Clone the repository:

```bash
git clone https://github.com/mohisha1205/build-your-own-shell.git
cd build-your-own-shell
```

Build the project:

```bash
cmake -S . -B build
cmake --build build
```

Run the shell:

```bash
./your_program.sh
```