#include <stdio.h>
// #include <string.h>
#include <stdlib.h>
// #include <termios.h>
#include <unistd.h>
#include "./libft/libft.h"
// #include <sys/types.h>
// #include <sys/stat.h>
#include <fcntl.h>
// #include <sys/wait.h>
// #include <signal.h>
// #include <dirent.h>
// #include <errno.h>
// #include <sys/ioctl.h>
// #include <curses.h>
// #include <term.h>
// #include <readline/readline.h>
// #include <readline/history.h>

typedef	struct	s_cmd
{
	char 	**args;
	int		kek;
} t_cmd;

void execute(char *infile, char *outfile, int numsimplecommands, t_cmd *scmd, int background)
{
	//save in/out
	int tmpin = dup(0);
	int tmpout = dup(1);
	//set the initial input
	int fdin;
	if (infile)
	{
		fdin = open(infile, O_RDONLY);
	}
	else
	{
		// Use default input
		fdin = dup(tmpin);
	}
	int ret;
	int fdout;
	int i;
	for(i = 0; i < numsimplecommands; i++)
	{
		//redirect input
		dup2(fdin, 0);
		close(fdin);
		//setup output
		if (i == numsimplecommands -1)
		{
			// Last simple command
			if(outfile)
			{
				fdout = open(outfile, O_RDWR | O_CREAT | O_TRUNC);
			}
			else
			{
				// Use default output
				fdout = dup(tmpout);
			}
		}
		else
		{
			// Not last
			//simple command
			//create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		// if/else
		// Redirect output
		dup2(fdout, 1);
		close(fdout);
		// Create child process
		ret = fork();
		if (ret == 0)
		{
			execvp(scmd[i].args[0], scmd[i].args);
			perror("execvp");
			exit(1);
		}
	}
	//  for
	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
	if (!background)
	{
		// Wait for last command
		waitpid(ret, NULL, 0);
	}
} 
// execute

int main (void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd) * 3);
	cmd[0].args = ft_split("ls -la", ' ');
	cmd[1].args = ft_split("grep as", ' ');
	cmd[2].args = ft_split("wc -w", ' ');
	execute(NULL, NULL, 3, cmd, 0);
	free(cmd);
	return (0);
}