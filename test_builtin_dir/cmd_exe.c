# include "test_builtin.h"

static int	abs_exe(char **str)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid < 0)
	{
		print_error("fork", NULL, errno);
		return (EXIT_FAILURE);
	}
	else if (pid == 0) // 子プロセスは親プロセスのデータをコピーしただけで書き換えることはできない
	{
		if (execve(str[0], str, NULL) == -1)
		{
			print_error(NULL, str[0], errno);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&wstatus) == -1)
			print_error("wait", NULL, errno);
		return (WEXITSTATUS(wstatus));
	}
	return (EXIT_SUCCESS);
}

static char	*get_path_value(t_envlist *envlist)
{
	while (envlist)
	{
		if (ft_strncmp("PATH", envlist->key, 5) == 0)
		{
			return (envlist->value);
		}
		envlist = envlist->next;
	}
	return (NULL);
}

static char	*get_absolute_path(char *str, char **split_path)
{
	size_t	i;
	char	*join_path;
	char	*join_slash;

	join_slash = ft_strjoin("/", str); // mallocしてる
	if (!join_slash)
	{
		print_error("malloc", NULL, errno);
		return (NULL);
	}
	i = 0;
	while (split_path[i])
	{
		join_path = ft_strjoin(split_path[i], join_slash); // mallocしてる
		if (!join_path)
		{
			print_error("malloc", NULL, errno);
			free(join_slash);
			return (NULL);
		}
		if (access(join_path, X_OK) == 0)
		{
			free(join_slash);
			return (join_path);
		}
		free(join_path);
		i++;
	}
	return (NULL);
}

static void	command_not_found(char *str)
{
	ft_putstr_fd("my_shell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

static int	rel_exe_main(char *absolute_path, char **str)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid < 0)
	{
		print_error("fork", NULL, errno);
		return (EXIT_FAILURE);
	}
	else if (pid == 0) // 子プロセスは親プロセスのデータをコピーしただけで書き換えることはできない
	{
		if (execve(absolute_path, str, NULL) == -1)
		{
			print_error(NULL, str[0], errno);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (wait(&wstatus) == -1)
			print_error("wait", NULL, errno);
		return (WEXITSTATUS(wstatus));
	}
	return (EXIT_SUCCESS);
}

static int	rel_exe(char **str, t_envlist *envlist)
{
	char	*path_value;
	char	**split_path;
	char	*absolute_path;
	int		exit_status;

	path_value = get_path_value(envlist);
	if (!path_value) // unset PATHされた場合
	{
		print_error(str[0], NULL, ENOENT); // errnoを決めうち
		return (127);
	}
	split_path = ft_split(path_value, ':');
	if (!split_path)
	{
		print_error("malloc", NULL, errno);
		return (EXIT_FAILURE);
	}
	absolute_path = get_absolute_path(str[0], split_path);
	if (!absolute_path)
	{
		command_not_found(str[0]);
		free_split(split_path);
		return (127);
	}
	exit_status = rel_exe_main(absolute_path, str);
	free(absolute_path);
	free_split(split_path);
	return (0);
}

int	cmd_exe(char **str, t_envlist *envlist) // strは2重配列で受け取る, つまりこの関数の前にlist_to_arrayの処理が必要
{
	int	exit_status;

	if (str[0][0] == '/')
		exit_status = abs_exe(str);
	else
		exit_status = rel_exe(str, envlist);
	return (exit_status);
}
