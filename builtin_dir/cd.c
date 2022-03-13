# include "libft/libft.h"

# include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h> // rl_clear_history, add_history
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <fcntl.h> // open
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h> // stat, lstat, fstat
# include <dirent.h> // opendir, readdir, closedir
# include <string.h> // strerror
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcsetattr, tcgetattr
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# include <limits.h> // macro
# include <stdint.h> // macro(linux)
# include <stdbool.h> // bool
# include <errno.h> // errno

void	safe_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	split_free(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
/* -------------------------------------------- */
int	my_cd(char **split_ln) // 環境変数の設定は未実装(PWD, OLDPWD)
{
	if (split_ln[1] == NULL)
	{
		// cd $HOMEは絶対でも相対でもないからやらなくていい
		return (0);
	}
	if (chdir(split_ln[1]) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**split_ln;
	int		exit_status;
	pid_t	pid;
	int		status;

	while (1)
	{
		line = readline("\033[33m""cd test(exit,pwd,lsも使える): ""\033[m"); // 入力受付
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			write(STDERR_FILENO, "exit\n", 5);
			safe_free(&line);
			return (EXIT_SUCCESS);
		}
		if (ft_strlen(line) == 0) // 改行だけの場合,空文字列がくる
		{
			safe_free(&line);
			continue ;
		}
		split_ln = ft_split(line, ' ');
		if (!split_ln)
		{
			safe_free(&line);
			return (EXIT_FAILURE);
		}
		if (ft_strncmp(split_ln[0], "cd", 3) == 0)
		{
			exit_status = my_cd(split_ln);
		}
		else if (ft_strncmp(split_ln[0], "pwd", 4) == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				safe_free(&line);
				return (EXIT_FAILURE);
			}
			else if (pid == 0) // 子プロセスは親プロセスのデータをコピーしただけで書き換えることはできない
			{
				if (execve("/bin/pwd", split_ln, envp) == -1)
				{
					perror("execve");
					return (EXIT_FAILURE);
				}
			}
			else
			{
				if (wait(&status) < 0)
				{
					write(STDERR_FILENO, "\n", 1);
					split_free(split_ln);
					safe_free(&line);
					return (EXIT_FAILURE);
				}
			}
		}
		else if (ft_strncmp(split_ln[0], "ls", 3) == 0)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				safe_free(&line);
				return (EXIT_FAILURE);
			}
			else if (pid == 0) // 子プロセスは親プロセスのデータをコピーしただけで書き換えることはできない
			{
				if (execve("/bin/ls", split_ln, envp) == -1)
				{
					perror("execve");
					return (EXIT_FAILURE);
				}
			}
			else
			{
				if (wait(&status) < 0)
				{
					write(STDERR_FILENO, "\n", 1);
					split_free(split_ln);
					safe_free(&line);
					return (EXIT_FAILURE);
				}
			}
		}
		else // cd,exit,pwd,ls以外
		{
			printf("Bad argument\n");
		}
		add_history(line); // 履歴の付け足し
		safe_free(&line);
		split_free(split_ln);
	}
	return (EXIT_SUCCESS);
}
