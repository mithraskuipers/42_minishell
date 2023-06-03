<p align="center" style="margin-bottom: 0px !important;">
  <img width="600" src="https://github.com/mithraskuipers/mithraskuipers/blob/master/readme_srcs/42/logo.png?raw=true" alt="42_Network_Amsterdam" align="center"> </p>
<h1 align="center" style="margin-top: 0px;">minishell <a href="https://github.com/JaeSeoKim/badge42"><img src="https://badge42.vercel.app/api/v2/cl483ajsd008309l6suq9l256/project/2709395" alt="mikuiper's 42 minishell Score" /></a></h1>

<p align="center" style="margin-top: 0px;">
<img src="https://forthebadge.com/images/badges/made-with-c.svg"/>
<img src="https://forthebadge.com/images/badges/built-with-love.svg"/>
</p>

## Introduction
The minishell project aims to recreate some of the functionalities of bash (Version 3.2). It provides a command-line interface for users to interact with the system. This project offers features similar to other shells, allowing users to execute commands, handle input/output redirections, and create pipelines.

## Authors
This minishell project was developed by [@rkieboom](https://github.com/rkieboom) and [@mikuiper](https://github.com/mikuiper).

## Structure
The minishell project is structured into four main components: Lexer, Parser, Expander, and Executor. Each component plays a specific role in the execution of commands.

### Lexer
The Lexer component receives user input and generates lexer tokens based on it. These lexer tokens are stored in a 2D character array. For example, the input "cat <<eof >file1 && cat file1 && abc || wc <file1 | cat >file2" would result in the following lexer tokens:

| lex_tok[0] | lex_tok[1] | lex_tok[2] | lex_tok[3] | lex_tok[4] | lex_tok[5] | lex_tok[6] | lex_tok[7] | lex_tok[8] | lex_tok[9] | lex_tok[10] | lex_tok[11] | lex_tok[12] | lex_tok[13] |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| `cat` | `<<eof` | `>file1` | `&&` | `cat` | `file1` | `&&` | `abc` | `\|\|` | `wc` | `<file1` | `\|` | `cat` | `>file2` |

### Parser
The Parser component checks for invalid syntax in the lexer tokens and creates a command table called parser tokens. The parser tokens contain information about the command, its arguments, and any associated redirections.

### Expander
The Expander component takes the parser tokens as input. It interprets environment variables, handles subshells, creates pipelines, and manages input/output redirections. Subshells are executed by creating child processes to run minishell without readline, directly passing the unparsed commands. After passing through the lexer, parser, and expander without errors, the executor is called.

### Executor
The Executor component executes the commands. If the command is a built-in command, it runs in the same process. Otherwise, it creates a child process to run the command. The executor handles input/output redirections and returns the exit code of the executed command.

## Example Outputs
### Wrong Syntax
If an incorrect syntax is detected, the message "Invalid Syntax at token" is displayed, and the error value `$?` is set to `258`.

### Invalid Command
If an invalid command is used, the message "Command not found" is displayed, and the error value `$?` is set to `127`.
