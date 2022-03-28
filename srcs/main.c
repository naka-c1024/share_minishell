/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:28:42 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/28 14:05:43 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = EXIT_SUCCESS;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_ms_ast	*ms_ast;
	t_envlist	*envlist;

	(void)argc;
	(void)argv;
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
		ms_ast = lexer_and_parser(line);
		// expanded_list = expander(ms_ast); expander関数でクオートと環境変数展開したlistを返し、それをexecutor関数の第一引数に渡す
		executor(ms_ast->cmd_info_list, &envlist);
		add_history(line); // 履歴の付け足し
		safe_free(&line);
	}
	return (g_exit_status);
}
