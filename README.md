# minishell
Basic Unix shell. 
### Recreating 50 years old technology (*almost*) from scratch
Supported features:
- [x] redirections of stdin and stdout (including <<heredoc)
- [x] pipelines
- [x] few built-ins (echo, cd, pwd, export, unset, exit, env)
- [x] variable expansion ($PATH, $USER etc.)
- [x] setting user variables (e.g. $foo=bar)
- [x] all features provided by GNU readline

Features yet to implement:
- * expansion
- AND-OR lists ("||" and "&&")
