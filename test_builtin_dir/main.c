# include "test_builtin.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**dbl_arr;
	int		exit_status;
	t_envlist	*envlist;


	(void)argc;
	(void)argv;
	exit_status = EXIT_SUCCESS;
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
