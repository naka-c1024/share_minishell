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
/* ---------------------------------------------------------------- */
int	read_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

bool	check_arg_value(char *str)
{
	size_t	i;
	size_t	len;
	int		sign;
	long long	abs_val;

	abs_val = 0;
	i = 0;
	len = ft_strlen(str);
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		sign = read_sign(str[i++]);
	while (ft_isdigit(str[i]))
	{
		if (sign == 1 && abs_val > (LONG_MAX - (str[i] - '0')) / 10)
			return (false);
		if (sign == -1 && (-1 * abs_val) < (LONG_MIN + (str[i] - '0')) / 10)
			return (false);
		abs_val *= 10;
		abs_val += str[i] - '0';
		i++;
	}
	if (len != i)
		return (false);
	return (true);
}

int	my_exit(char **split_ln)
{
	size_t	cnt;
	long	arg_value;

	cnt = 0;
	while (split_ln[cnt] != NULL && cnt < 3)
		cnt++;
	if (cnt == 1)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		return (EXIT_SUCCESS);
	}
	else if (cnt > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	else if (check_arg_value(split_ln[1]) == false) // オーバーフローと文字を見る
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		printf("bash: exit: %s: numeric argument required\n", split_ln[1]);
		return (255);
	}
	arg_value = atol(split_ln[1]); // 実装する
	ft_putendl_fd("exit", STDERR_FILENO);
	return (arg_value);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**split_ln;
	int		exit_status;
	pid_t pid;
	int status;

	while (1)
	{
		line = readline("\033[33m""exit test: ""\033[m"); // 入力受付
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
			if (exit_status != 1)
			{
				split_free(split_ln);
				safe_free(&line);
				return (exit_status);
			}
		}
		else // exitしか受け付けない
		{
			printf("Bad argument\n");
		}
		add_history(line); // 履歴の付け足し
		safe_free(&line);
		split_free(split_ln);
	}
	return (EXIT_SUCCESS);
}
