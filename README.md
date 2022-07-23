# minishell
Basic Unix shell. 
### Recreating 50 years old technology (*almost*) from scratch
Supported features:
- redirections of stdin and stdout (including <<heredoc)
- pipelines
- few built-ins (echo, cd, pwd, export, unset, exit, env)
- variable expansion ($PATH, $USER etc.)
- setting user variables (e.g. $foo=bar)
- all features provided by GNU readline
* Features yet to implement:
- "*" expansion
- AND-OR lists ("||" and "&&")
