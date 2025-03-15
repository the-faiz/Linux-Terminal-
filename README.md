# Linux Terminal Emulator (C++)

## Overview
The **Linux Terminal Emulator** is a project implemented in C++ that replicates the functionality of a Linux terminal. This project allows users to interact with the system using command-line instructions and provides functionalities similar to a native terminal.

## Features
- Process creation and external command execution
- Input and output redirection
- Background execution of commands
- Pipe mode for multiple commands
- Handling signals for interrupting and background execution
- Implementing `cd` and `pwd` commands
- Handling wildcards (`*` and `?`)
- Command history navigation using up/down arrow keys
- Detecting malware using a custom `sb` command
- Checking file locks with the `delep` command
- Command line editing features (`Ctrl + A`, `Ctrl + E`)

## Installation
### Prerequisites
- Linux operating system
- C++ compiler (e.g., `g++`)
- GNU Readline Library (optional, for command history)

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/the-faiz/Linux-Terminal-
   ```
2. Navigate to the project directory:
   ```bash
   cd Linux-Terminal-
   ```
3. Build the project using `make`:
   ```bash
   make
   ```
4. Run the kernel program:
   ```bash
   ./kernel_program
   ```

## Usage
- Run external commands with input/output redirection:
  ```bash
  ./a.out < input.txt > output.txt
  ```
- Execute commands in the background:
  ```bash
  ./myprog &
  ```
- Use pipes for multiple commands:
  ```bash
  ls | sort | more
  ```
- Detect malware with the `sb` command:
  ```bash
  sb <pid> -suggest
  ```
- Check for file locks with the `delep` command:
  ```bash
  delep <file_path>
  ```

## Contact
For any issues or suggestions, feel free to reach out to me at atiffaizan001@gmail.com

---

