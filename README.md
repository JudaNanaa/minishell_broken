# Minishell

A comprehensive implementation of a Unix shell written in C, featuring advanced parsing, execution, and shell functionality.

## 📋 Table of Contents
- [Minishell](#minishell)
	- [📋 Table of Contents](#-table-of-contents)
	- [🎯 Overview](#-overview)
	- [✨ Features](#-features)
		- [Core Shell Functionality](#core-shell-functionality)
		- [Advanced Parsing](#advanced-parsing)
		- [Redirections \& Pipes](#redirections--pipes)
		- [Wildcard Expansion](#wildcard-expansion)
		- [Additional Features](#additional-features)
	- [🏗️ Project Structure](#️-project-structure)
	- [🚀 Installation](#-installation)
		- [Prerequisites](#prerequisites)
		- [Build Instructions](#build-instructions)
		- [Build Options](#build-options)
	- [💻 Usage](#-usage)
		- [Interactive Mode](#interactive-mode)
		- [Command Mode](#command-mode)
		- [Example Commands](#example-commands)
	- [🔧 Built-in Commands](#-built-in-commands)
	- [🎯 Advanced Features](#-advanced-features)
		- [Parsing Engine](#parsing-engine)
		- [Execution Engine](#execution-engine)
		- [Memory Management](#memory-management)
	- [🧪 Testing](#-testing)
		- [Basic Tests](#basic-tests)
		- [Bonus Features Tests](#bonus-features-tests)
		- [Specific Feature Tests](#specific-feature-tests)
		- [Memory Leak Testing](#memory-leak-testing)
		- [Run All Tests](#run-all-tests)
	- [🛠️ Development](#️-development)
		- [Code Style](#code-style)
		- [Debugging](#debugging)
	- [👥 Contributors](#-contributors)
	- [🔍 Technical Details](#-technical-details)
		- [Architecture](#architecture)
		- [Key Components](#key-components)

## 🎯 Overview

Minishell is a complete shell implementation that replicates the behavior of bash, including command parsing, execution, environment variable management, and advanced shell features. The project demonstrates deep understanding of system programming, process management, and shell internals.

## ✨ Features

### Core Shell Functionality
- **Interactive shell** with custom prompt
- **Command execution** with proper process management
- **Environment variable** handling and expansion
- **Signal handling** (Ctrl+C, Ctrl+D, Ctrl+\)
- **Exit status** management
- **Subshell execution** with `-c` option

### Advanced Parsing
- **Lexical analysis** with tokenization
- **Abstract Syntax Tree (AST)** construction
- **Quote handling** (single and double quotes)
- **Variable expansion** with proper escaping
- **Command chaining** with `&&` and `||` operators

### Redirections & Pipes
- **Input redirection** (`<`)
- **Output redirection** (`>`, `>>`)
- **Here documents** (`<<`)
- **Pipes** (`|`) with multiple pipe support
- **File descriptor** management

### Wildcard Expansion
- **Glob pattern matching** (`*`)
- **Directory traversal** for wildcard expansion
- **Path resolution** with absolute and relative paths

### Additional Features
- **Command history** with readline integration
- **Alias support** with persistent storage
- **Custom prompt** with user and directory display
- **Garbage collection** for memory management
- **Comprehensive error handling**

## 🏗️ Project Structure

```
minishell/
├── includes/           # Header files
│   ├── minishell.h
│   ├── includes.h
│   └── error.h
├── srcs/              # Source code
│   ├── main.c         # Entry point
│   ├── ast/           # Abstract Syntax Tree
│   ├── builtins/      # Built-in commands
│   ├── exec/          # Command execution
│   ├── parsing/       # Lexer and parser
│   ├── wildcard/      # Wildcard expansion
│   ├── features/      # History, prompt, aliases
│   ├── signal/        # Signal handling
│   ├── environment/   # Environment management
│   ├── garbage_collector/ # Memory management
│   └── utils/         # Utility functions
├── libft/             # Custom C library
├── bin/               # Test scripts
└── Makefile           # Build configuration
```

## 🚀 Installation

### Prerequisites
- GCC compiler
- Make
- Readline library
- Linux/Unix environment

### Build Instructions

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd minishell
   ```

2. **Compile the project**
   ```bash
   make
   ```

3. **Run minishell**
   ```bash
   ./minishell
   ```

### Build Options
- `make all` - Compile the project
- `make clean` - Remove object files
- `make fclean` - Remove all generated files
- `make re` - Rebuild the project
- `make leak` - Run with Valgrind for memory leak detection

## 💻 Usage

### Interactive Mode
```bash
./minishell
```

### Command Mode
```bash
./minishell -c "echo Hello World"
```

### Example Commands
```bash
# Basic commands
ls -la
pwd
echo "Hello World"

# Environment variables
export MY_VAR="test"
echo $MY_VAR

# Pipes and redirections
ls -l | grep ".c" > output.txt
cat < input.txt

# Command chaining
ls && echo "Success" || echo "Failed"

# Wildcards
ls *.c
echo /usr/bin/*

# Here documents
cat << EOF
This is a here document
EOF
```

## 🔧 Built-in Commands

| Command | Description									| Example							|
|---------|-----------------------------|---------------------|
| `echo`	| Print arguments							| `echo "Hello World"`|
| `cd`		| Change directory 						| `cd /home/user`			|
| `pwd`		| Print working directory 		| `pwd` 							|
| `export`| Set environment variables 	| `export VAR=value`	|
| `unset`	| Unset environment variables | `unset VAR`					|
| `env`		| Print environment variables | `env`								|
| `exit`	| Exit the shell							| `exit 0`						|
| `alias`	| Create command aliases 			| `alias ll="ls -la"` |

## 🎯 Advanced Features

### Parsing Engine
- **Lexical Analysis**: Tokenizes input into meaningful units
- **Syntax Analysis**: Builds Abstract Syntax Tree for command structure
- **Error Recovery**: Handles syntax errors gracefully

### Execution Engine
- **Process Management**: Fork/exec for command execution
- **Signal Handling**: Proper signal propagation and handling
- **File Descriptor Management**: Redirection and pipe implementation

### Memory Management
- **Garbage Collection**: Automatic memory cleanup
- **Memory Safety**: Comprehensive error handling and cleanup

## 🧪 Testing

The project includes comprehensive test suites:

### Basic Tests
```bash
./bin/test_basic.sh
```

### Bonus Features Tests
```bash
./bin/test_bonus.sh
```

### Specific Feature Tests
```bash
./bin/test_cd.sh      # Directory navigation
./bin/test_echo.sh    # Echo command
./bin/test_export.sh  # Environment variables
./bin/test_pipes.sh   # Pipe functionality
```

### Memory Leak Testing
```bash
./bin/test_valgrind.sh
```

### Run All Tests
```bash
./bin/run_test.sh
```

## 🛠️ Development

### Code Style
- Follows 42 coding standards
- Uses custom `libft` library
- Comprehensive error handling
- Memory leak prevention

### Debugging
```bash
make debug    # Launch with LLDB debugger
make leak     # Run with Valgrind
```

## 👥 Contributors

- **[JudaNanaa](https://github.com/JudaNanaa)**
- **[iibabyy](https://github.com/iibabyy)**

## 🔍 Technical Details

### Architecture
- **Modular Design**: Separated concerns with clear interfaces
- **AST-based Parsing**: Robust command structure representation
- **Process-based Execution**: Proper Unix process management
- **Memory Safety**: Garbage collection and error handling

### Key Components
- **Lexer**: Tokenizes shell input
- **Parser**: Builds command structure
- **Executor**: Manages process execution
- **Builtins**: Implements shell commands
- **Environment**: Manages variables and state

---

*This minishell implementation demonstrates advanced C programming concepts, system programming, and shell internals understanding.*
