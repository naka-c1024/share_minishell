# include "test_builtin.h"

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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**split_ln;
	int		exit_status;
	pid_t	pid;
	int		status;

	t_envlist	*envlist;
	exit_status = EXIT_SUCCESS;

	(void)argc;
	(void)argv;

	envlist = create_envlist(envp); // freeするときはfree_list(envlist)する

	while (1)
	{
		line = readline(RL_MSG); // 入力受付
		if (ft_strlen(line) == 0) // 改行だけの場合,空文字列がくる
		{
			safe_free(&line);
			continue ;
		}
		split_ln = ft_split(line, ' ');
		if (!split_ln)
		{
			safe_free(&line);
			free_list(envlist);
			return (EXIT_FAILURE);
		}
		if (ft_strncmp(split_ln[0], "exit", 5) == 0)
		{
			exit_status = my_exit(split_ln);
			if (exit_status != 1) // これ大事, 1の時はexitしない
			{
				split_free(split_ln);
				safe_free(&line);
				free_list(envlist);
				return (exit_status);
			}
		}
		else if (ft_strncmp(split_ln[0], "echo", 5) == 0)
			exit_status = my_echo(split_ln);
		else if (ft_strncmp(split_ln[0], "cd", 3) == 0)
			exit_status = my_cd(split_ln, &envlist);
		else if (ft_strncmp(split_ln[0], "pwd", 4) == 0)
			exit_status = my_pwd();
		else if (ft_strncmp(split_ln[0], "unset", 6) == 0)
			exit_status = my_unset(split_ln, &envlist);
		else if (ft_strncmp(split_ln[0], "env", 4) == 0)
			exit_status = my_env(envlist);
		else if (ft_strncmp(split_ln[0], "export", 7) == 0)
			exit_status = my_export(split_ln, &envlist);
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
					free_list(envlist);
					return (EXIT_FAILURE);
				}
			}
		}
		else
			printf("Bad argument\n");
		add_history(line); // 履歴の付け足し
		safe_free(&line);
		split_free(split_ln);
	}
	return (exit_status);
}
