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

#include "libft/libft.h"

int	my_echo(char **split_ln) // 引数はexecveの第二引数が来るものとして考える
{
	int	exit_value; // 本家コード見た感じ0以外は無さそう? 強いて言うならwriteが失敗した時くらい?
	int	display_return;
	size_t	i;

	display_return = 1;
	exit_value = 0;
	i = 0;
	if (split_ln[++i] == NULL) // listの最後がnull埋めされている前提
	{
		write(1, "\n", 1);
		return (exit_value);
	}
	if (strncmp(split_ln[i], "-n", 3) == 0)
	{
		display_return = 0;
		i++;
	}
	while (split_ln[i])
	{
		printf("%s", split_ln[i]);
		if (split_ln[i + 1])
			putchar(' ');
		i++;
	}
	if (display_return)
		putchar('\n');
	return (exit_value);
}

int	main(int argc, char **argv, char **envp)
{
	int	exit_value;
	char	**split_ln;

	if (argc == 1 || strncmp("echo", argv[1], 5) != 0)
	{
		write(STDERR_FILENO, "Bad argument\n", 13);
		return (0);
	}
	split_ln = &argv[1]; // 最初のa.outを飛ばす

	exit_value = my_echo(split_ln); // 引数はexecveの第二引数が来るものとして考える
	return (exit_value);
}