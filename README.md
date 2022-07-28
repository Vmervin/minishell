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

### Download package
You can download container with minishell and mount it on your disk
Use command `docker run --rm -it -v "$HOME:/home" ghcr.io/provology/minishell:main` where `--rm` means delete container after exit, `-it` allocates terminal inside container and allow to interact with it, `-v "$HOME:/home"` mount (link) the host's HOME directory to the container's /home directory (You may choose another directorys, just remember that docker requires absolute paths for binding mounts. For example instead of `$HOME` type `/your/path/to/target/directory`) As result if `cd` to your container's `/home` directory you'll see content of your host HOME directory and if you make modifications they appear in host too. However scope of minishell is limited by directory specified in run command and you can't see other directories from minishell.
