/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:28:42 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/12 16:55:28 by ynakashi         ###   ########.fr       */
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
			safe_func(write(STDERR_FILENO, "exit\n", 5));
			exit (EXIT_SUCCESS);//ここ、returnからexitに変えました
		}
		init_signal(SIGINT, sigint_after_rl);
		init_signal(SIGQUIT, sigquit_after_rl); // プロセス実行時は無視できないのでこれを使う, here docの後に書くことができるのでもし行数が足りなければこの行は削除する
		if (ft_strlen(line) == 0) // 改行だけの場合,空文字列がくる
		{
			safe_free(&line);
			continue ;
		}
		ms_ast = lexer_and_parser(&line, &process_cnt);
		if (ms_ast)
		{
			here_doc_set(ms_ast);
			expander(&ms_ast, envlist);
			executor(ms_ast, &envlist, process_cnt);
		}
		add_history(line); // 履歴の付け足し
		safe_free(&line);
	}
	return (g_exit_status);
}
