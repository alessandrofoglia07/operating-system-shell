<h1 align="center">
  <br>
  Operating System Shell
</h1>

<h4 align="center">Custom Operating System Shell implementation written in C</h4>

<p align="center">
  <a href="#key-features">Key Features</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#license">License</a>
</p>

## Key Features

- **Command Execution**: Supports execution of common shell commands such as cd, pwd, ls, clear, echo, set, unset, and exit.
- **Alias Management**: Allows users to create and manage command aliases for easier command execution.
- **ANSI Escape Codes**: Utilizes ANSI escape codes for colored terminal output and console clearing.
- **Pipes Handling**: Supports piping between commands, enabling complex command chaining.
- **Input/Output Redirection**: Handles input and output redirection for commands.
- **Signal Handling**: Manages signals like SIGINT and SIGTSTP to control shell behavior.
- **Tokenization**: Efficiently tokenizes input commands for processing.
- **Dynamic Command Handling**: Dynamically handles various commands and runs them in the shell environment.

## How To Use

To clone and run this application, you'll need [Git](https://git-scm.com) and [CMake](https://cmake.org/)
From your command line:

```bash
# Clone this repository
$ git clone https://github.com/alessandrofoglia07/operating-system-shell

# Go into the repository
$ cd operating-system-shell

# Build the program
$ cmake --build ./cmake-build-debug --target operating_system_shell -- -j 6

# Run the program 
$ ./build/operating_system_shell <ip>
```

<img src="https://cloud-gts4uwzbv-hack-club-bot.vercel.app/0image.png"></img>

## License

MIT

---

> GitHub [@alessandrofoglia07](https://github.com/alessandrofoglia07) &nbsp;&middot;&nbsp;
> StackOverflow [@Alexxino](https://stackoverflow.com/users/21306952/alexxino) &nbsp;&middot;&nbsp;
> NPM [alessandrofoglia07](https://www.npmjs.com/~alessandrofoglia07)
