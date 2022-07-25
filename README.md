# minishell
### Basic Unix shell for everyday use
Attempt to recreate 40 years old technology (*almost*) from scratch

Supported features:
- [x] redirections of stdin and stdout (including <<heredoc)
- [x] pipelines
- [x] few built-ins (echo, cd, pwd, export, unset, exit, env)
- [x] variable expansion ($PATH, $USER etc.)
- [x] special parameters expansion (only $?)
- [x] setting user variables (e.g. $foo=bar)
- [x] all features provided by GNU readline

Features yet to implement:
- [ ] \* wildcard expansion
- [ ] AND-OR lists ("||" and "&&")

### Building
To build minishell you will need GNU Readline library installed. Detailed information on how to install GNU Readline provided on [official website](https://tiswww.cwru.edu/php/chet/readline/rltop.html)

`make` to compile `./minishell` to run
