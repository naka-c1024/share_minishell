/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:28:42 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/25 20:38:40 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**two_dim_arr;
	int		exit_status;
	t_envlist	*envlist;

	(void)argc;
	(void)argv;
	exit_status = EXIT_SUCCESS;
	envlist = create_envlist(envp); // freeするときはfree_list(envlist)する

	while (1)
	{
		init_signal(SIGINT, sigint_before_rl);
		init_signal(SIGQUIT, SIG_IGN); // SIGQUITを無視
		line = readline(RL_MSG); // 入力受付
		if (!line) // ctrl+DではsignalではなくEOFが送られる,readlineはEOFを受け取ったらNULLを返す
		{
			write(STDERR_FILENO, "exit\n", 5);
			return (EXIT_SUCCESS);
		}
		init_signal(SIGINT, sigint_after_rl);
		init_signal(SIGQUIT, sigquit_after_rl); // プロセス実行時は無視できないのでこれを使う
		if (ft_strlen(line) == 0) // 改行だけの場合,空文字列がくる
		{
			safe_free(&line);
			continue ;
		}

		// ここをms_ast = lexer_and_parser()に変えてください！
		two_dim_arr = ft_split(line, ' ');
		if (!two_dim_arr)
		{
			safe_free(&line);
			free_list(envlist);
			return (EXIT_FAILURE);
		}

		// expander関数でクオートと環境変数展開
		// executor関数の中でlst_to_arrしてパイプやリダイレクトの処理してonly_one_cmd実行
		exit_status = only_one_cmd(two_dim_arr, &envlist);

		add_history(line); // 履歴の付け足し
		safe_free(&line);
		free_split(two_dim_arr);
	}
	return (exit_status);
}
