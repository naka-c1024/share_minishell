# include <readline/readline.h> // rl
# include <readline/history.h> // rl histroy
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname
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

# include "libft/libft.h"

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

int	my_exit(char **split_ln)
{
	int	exit_status;

	write(STDERR_FILENO, "exit\n", 5);
	exit_status = EXIT_SUCCESS;
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**split_ln;
	int		exit_status;

	while (1)
	{
		line = readline("exit test: "); // 入力受付
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
		if (ft_strncmp(split_ln[0], "exit", 5) == 0)
		{
			exit_status = my_exit(split_ln);
			split_free(split_ln);
			safe_free(&line);
			return (exit_status);
		}
		else
		{
			printf("Bad argument\n");
		}
		add_history(line); // 履歴の付け足し
		safe_free(&line);
		split_free(split_ln);
	}
	return (EXIT_SUCCESS);
}
