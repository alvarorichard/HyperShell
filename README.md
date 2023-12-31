<p align="center">
  <img src="https://i.imgur.com/OIO9XyE.png" alt="Imagem logo" />
</p>


# HyperShell
HyperShell is a simple shell implementation in C. It provides a command line interface for users to interact with the operating system.

## Features
* Command execution
* Built-in commands: cd, help, exit
* Command line history is not supported in this version

## Requirements

* Clang/LLVM 
* GCC

## Usage

```shell

git clone https://github.com/alvarorichard/HyperShell.git
``````

```shell
cd HyperShell/src
```
# Run
 just run this script for compile and run

 ```shell
 sudo ./install.sh
 ```
 You will be greeted with a >> prompt. Here you can type commands and parameters, and press enter to execute them.

## Built-in Commands

* cd [directory]: Change the current directory to [directory]. If no directory is specified, an error message is displayed.

* help: Displays information about the built-in commands.

*  Supports external commands `ls`,`cat`,`echo` and `touch`

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Notes 
* Please do not run the code in Zig, it is still in testing and development. It is the same project but rewritten in Zig. Please do not consider the Zig code
