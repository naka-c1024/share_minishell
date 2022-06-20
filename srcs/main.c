/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:28:42 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/20 11:39:13 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = EXIT_SUCCESS;

static void	ms_component(char **line, t_envlist **envlist)
{
	t_ms_ast	*ms_ast;
	size_t		process_cnt;

	ms_ast = lexer_and_parser(line, &process_cnt);
	if (ms_ast
		&& here_doc_init(ms_ast) == true
		&& expander(&ms_ast, *envlist) == true)
	{
		executor(ms_ast, envlist, process_cnt);
	}
	add_history(*line);
	safe_free(line);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_envlist	*envlist;

	(void)argc;
	(void)argv;
	envlist = create_envlist(envp);
	while (1)
	{
		init_signal(SIGINT, sigint_before_rl);
		init_signal(SIGQUIT, SIG_IGN);
		line = readline(RL_MSG);
		if (!line)
		{
			safe_func(write(STDERR_FILENO, "exit\n", 5));
			exit (g_exit_status);
		}
		if (ft_strlen(line) == 0)
		{
			safe_free(&line);
			continue ;
		}
		ms_component(&line, &envlist);
	}
}
