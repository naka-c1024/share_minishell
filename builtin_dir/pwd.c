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

int	my_pwd(void)
{
	char	*pwd_buf;

	pwd_buf = getcwd(NULL, 0);
	if (pwd_buf == NULL)
	{
		if (errno == ENOENT)
			write(STDERR_FILENO, "No such file or directory\n", 26);
		if (errno == EACCES)
			write(STDERR_FILENO, "Permission denied\n", 18);
		if (errno == ENAMETOOLONG)
			write(STDERR_FILENO, "File name too long\n", 19);
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd_buf);
	free(pwd_buf);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp) // 引数はexecveの第二引数が来るものとして考える
{
	int	exit_value;

	if (argc == 1 || strncmp("pwd", argv[1], 4) != 0)
	{
		write(STDERR_FILENO, "Bad argument\n", 13);
		return (0);
	}
	exit_value = my_pwd();
	return (exit_value);
}