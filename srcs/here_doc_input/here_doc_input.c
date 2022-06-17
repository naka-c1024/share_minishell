/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:18:00 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/17 14:06:43 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc_input.h"

static size_t	get_here_doc_init(t_ms_ast *ms_ast, char *delimiter)
{
	size_t	len;

	free(ms_ast->buffer);//これ必要なはずかつ、callocで作ってるはずだから最初ダブルフリー起きないはず
	free(ms_ast->delimiter);
	ms_ast->buffer = ft_x_strdup("");
	len = ft_strlen(delimiter);
	ms_ast->delimiter = (char *)ft_x_calloc(len + 1, sizeof(char));
	ft_strlcpy(ms_ast->delimiter, delimiter, len + 1);
	ms_ast->delimiter[len] = '\n';
	return (len);
}

static size_t	make_buffer(t_ms_ast *ms_ast, char *delimiter)
{
	size_t	len;
	char	*a_temp;
	char	*b_temp;
	char	*new_document;

	ms_ast->is_here_doc = true;
	len = get_here_doc_init(ms_ast, delimiter);
	b_temp = readline("> ");
	if (!b_temp)
	{
		return (0);
	}
	a_temp = ft_x_strjoin(b_temp, "\n");
	free(b_temp);
	while (ft_strncmp(a_temp, ms_ast->delimiter, len + 1))
	{
		new_document = ft_x_strjoin(ms_ast->buffer, a_temp);
		free(ms_ast->buffer);
		free(a_temp);
		ms_ast->buffer = new_document;
		b_temp = readline("> ");
		if (!b_temp)
		{
			return (0);
		}
		a_temp = ft_x_strjoin(b_temp, "\n");
		free(b_temp);
	}
	free(a_temp);
	return (ft_strlen(ms_ast->buffer));
}

static void	receive_buffer(t_ms_ast *ms_ast, int pipefd[2])
{
	char	*temp1;
	char	*temp2;
	int		read_flag;

	read_flag = 0;
	ms_ast->buffer = ft_x_strdup("");
	while (1)
	{
		temp1 = ms_ast->buffer;
		temp2 = (char *)ft_x_calloc(101, sizeof(char));
		read_flag = safe_func(read(pipefd[0], temp2, 100));
		if (read_flag == 0)
		{
			free(temp2);
			return ;
		}
		ms_ast->buffer = ft_x_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
	}
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
	{
		write(pipefd[1], cmd_node->buffer, len + 1);
	}
}

static void	crawl_ast(t_ms_ast *ms_ast, int pipefd[2])
{
	if (ms_ast->left_node && ms_ast->type == PIPE)
		crawl_ast(ms_ast->left_node, pipefd);
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
	int		wstatus;

	safe_func(pipe(pipefd));
	pid = fork();
	if (pid == 0)
	{
		init_signal(SIGINT, sigint_after_rl_in_heredoc); // here docが終わったらまた元のルールに設定する
		safe_func(close(pipefd[0]));
		crawl_ast(ms_ast, pipefd);
		exit(0);
	}
	else
	{
		safe_func(close(pipefd[1]));
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
	}
	return (true);
}

bool	here_doc_init(t_ms_ast *ms_ast)
{
	bool	is_signal;

	init_signal(SIGQUIT, SIG_IGN); // here docの中ではSIGQUITを無視
	init_signal(SIGINT, SIG_IGN); // SIGQUITを無視
	is_signal = here_doc_set(ms_ast);
	init_signal(SIGQUIT, sigquit_after_rl); // here docが終わったらまた元のルールに設定する
	init_signal(SIGINT, sigint_after_rl); // here docが終わったらまた元のルールに設定する
	return (is_signal);
}
