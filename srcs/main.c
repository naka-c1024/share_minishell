/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:28:42 by ynakashi          #+#    #+#             */
/*   Updated: 2022/05/13 15:14:37 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = EXIT_SUCCESS;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_ms_ast	*ms_ast;
	t_envlist	*envlist;
	size_t		process_cnt;

	(void)argc;
	(void)argv;
	envlist = create_envlist(envp);
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
		ms_ast = lexer_and_parser(line, &process_cnt);
		here_doc_set(ms_ast);
		//envlist = create_envlist(envp); // freeするときはfree_list(envlist)する
		expander(&ms_ast, envlist); // expander関数でms_astを書き換える
		executor(ms_ast, &envlist, process_cnt);
		add_history(line); // 履歴の付け足し
		safe_free(&line);
	}
	return (g_exit_status);
}
