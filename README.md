# Simple Shell in C

## Project Overview

This version of the simple shell includes support for command history, colored prompts, and more. It still supports basic Unix commands, `cd`, `exit`, and includes a built-in `history` command.

### New Features:
- **History Command**: View the history of entered commands by typing `history`.
- **Colored Prompt**: The shell prompt is now colored green for better aesthetics.
- **Exit Command**: Type `exit` to terminate the shell as before.

## How to Build and Run

1. Clone this repository to your local machine:
    ```bash
    git clone https://github.com/ArijSaaleh/shell-simulation.git
    cd shell-simulation
    ```

2. Compile the project using `gcc`:
    ```bash
    gcc -o shell shell.c
    ```

3. Run the shell:
    ```bash
    ./shell
    ```

## Usage

### Basic Commands
You can run commands like:
```bash
arijs-shell> ls
arijs-shell> pwd
arijs-shell> echo "Hello, Shell!"
```

# License
This project is open-source.