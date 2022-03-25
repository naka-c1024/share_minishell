# include "test_builtin.h"

int	only_one_cmd(char **dbl_arr, t_envlist **envlist)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ft_strncmp(dbl_arr[0], "exit", 5) == 0)
	{
		exit_status = my_exit(dbl_arr);
		if (exit_status != 1) // これ大事, 1の時はexitしない、しかしexit 1や前のexit_statusが1の時はexitする, ここでmallocしてるもの全てfreeする
			exit(exit_status);
	}
	else if (ft_strncmp(dbl_arr[0], "echo", 5) == 0)
		exit_status = my_echo(dbl_arr);
	else if (ft_strncmp(dbl_arr[0], "cd", 3) == 0)
		exit_status = my_cd(dbl_arr, envlist);
	else if (ft_strncmp(dbl_arr[0], "pwd", 4) == 0)
		exit_status = my_pwd();
	else if (ft_strncmp(dbl_arr[0], "unset", 6) == 0)
		exit_status = my_unset(dbl_arr, envlist);
	else if (ft_strncmp(dbl_arr[0], "env", 4) == 0)
		exit_status = my_env(*envlist);
	else if (ft_strncmp(dbl_arr[0], "export", 7) == 0)
		exit_status = my_export(dbl_arr, envlist);
	else
		exit_status = cmd_exe(dbl_arr, *envlist);
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**dbl_arr;
	int		exit_status;
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
		dbl_arr = ft_split(line, ' ');
		if (!dbl_arr)
		{
			safe_free(&line);
			free_list(envlist);
			return (EXIT_FAILURE);
		}
		// パイプやリダイレクトの処理
		exit_status = only_one_cmd(dbl_arr, &envlist);
		add_history(line); // 履歴の付け足し
		safe_free(&line);
		free_split(dbl_arr);
	}
	return (exit_status);
}
