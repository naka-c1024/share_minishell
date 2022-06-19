/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:18:00 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/18 22:31:12 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc_input.h"

static bool	proccess_disporsal(pid_t pid, int pipefd[2], t_ms_ast *ms_ast)
{
	int	wstatus;

	wstatus = 0;
	if (safe_func(waitpid(pid, &wstatus, WUNTRACED)))
	{
		if (WIFSIGNALED(wstatus))
		{
			safe_func(close(pipefd[0]));
			return (false);
		}
		receive_buffer(ms_ast, pipefd);
		safe_func(close(pipefd[0]));
	}
	return (true);
}

static void	here_doc_set_table(t_ms_ast *cmd_node, int pipefd[2])
{
	t_list	*tmp_node;
	size_t	len;

	tmp_node = cmd_node->cmd_info_list;
	len = 0;
	while (tmp_node)
	{
		if (!ft_strncmp(tmp_node->content, "<<", 2))
		{
			len = make_buffer(cmd_node, tmp_node->next->content);
			tmp_node = tmp_node->next->next;
		}
		else
			tmp_node = tmp_node->next;
	}
	if (len)
		write(pipefd[1], cmd_node->buffer, len + 1);
}

static void	crawl_ast_in_hdi(t_ms_ast *ms_ast, int pipefd[2])
{
	if (ms_ast->left_node && ms_ast->type == PIPE)
		crawl_ast_in_hdi(ms_ast->left_node, pipefd);
	if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
		here_doc_set_table(ms_ast->right_node, pipefd);
	if (ms_ast->cmd_info_list)
		here_doc_set_table(ms_ast, pipefd);
	return ;
}

static bool	here_doc_set(t_ms_ast *ms_ast)
{
	pid_t	pid;
	int		pipefd[2];

	safe_func(pipe(pipefd));
	pid = fork();
	if (pid == 0)
	{
		init_signal(SIGINT, sigint_after_rl_in_heredoc);
		safe_func(close(pipefd[0]));
		crawl_ast_in_hdi(ms_ast, pipefd);
		exit(0);
	}
	else
	{
		safe_func(close(pipefd[1]));
		return (proccess_disporsal(pid, pipefd, ms_ast));
	}
	return (true);
}

bool	here_doc_init(t_ms_ast *ms_ast)
{
	bool	is_signal;

	init_signal(SIGQUIT, SIG_IGN);
	init_signal(SIGINT, SIG_IGN);
	is_signal = here_doc_set(ms_ast);
	init_signal(SIGQUIT, sigquit_after_rl);
	init_signal(SIGINT, sigint_after_rl);
	return (is_signal);
}
