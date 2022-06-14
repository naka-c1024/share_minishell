/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:18:00 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/14 12:07:26 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc_input.h"

static size_t	get_here_doc_init(t_ms_ast *ms_ast, char *delimiter)
{
	size_t	len;

	ms_ast->buffer = ft_x_strdup("");
	len = ft_strlen(delimiter);
	ms_ast->delimiter = (char *)ft_x_calloc(len + 1, sizeof(char));
	ft_strlcpy(ms_ast->delimiter, delimiter, len + 1);
	ms_ast->delimiter[len] = '\n';
	return (len);
}

static void	make_buffer(t_ms_ast *ms_ast, char *delimiter, int pipefd[2])
{
	size_t	len;
	char	*a_temp;
	char	*b_temp;
	char	*new_document;

	ms_ast->is_here_doc = true;
	len = get_here_doc_init(ms_ast, delimiter);
	b_temp = readline(">");
	a_temp = ft_x_strjoin(b_temp, "\n");
	free(b_temp);
	while (ft_strncmp(a_temp, ms_ast->delimiter, len + 1))
	{
		new_document = ft_x_strjoin(ms_ast->buffer, a_temp);
		free(ms_ast->buffer);
		free(a_temp);
		ms_ast->buffer = new_document;
		b_temp = readline(">");
		a_temp = ft_x_strjoin(b_temp, "\n");
		free(b_temp);
	}
	free(a_temp);
	len = ft_strlen(ms_ast->buffer);
	write(pipefd[1], ms_ast->buffer, len + 1);
	exit(0);
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

static void	set_here_doc(t_ms_ast *ms_ast, char *delimiter)
{
	pid_t	pid;
	int		pipefd[2];
	int		wstatus;

	safe_func(pipe(pipefd));
	pid = safe_func(fork());
	if (pid == 0)
	{
		safe_func(close(pipefd[0]));
		make_buffer(ms_ast, delimiter, pipefd);
	}
	else
	{
		safe_func(close(pipefd[1]));
		if ((waitpid(pid, &wstatus, WUNTRACED) == -1) && (WIFSIGNALED(wstatus) == false))
			safe_func(-1);
		receive_buffer(ms_ast, pipefd);
		safe_func(close(pipefd[0]));
	}
}

static void	here_doc_set_table(t_ms_ast *cmd_node)
{
	t_list	*tmp_node;

	tmp_node = cmd_node->cmd_info_list;
	while (tmp_node)
	{
		if (!ft_strncmp(tmp_node->content, "<<", 2))
		{
			init_signal(SIGQUIT, SIG_IGN); // here docの中ではSIGQUITを無視
			set_here_doc(cmd_node, tmp_node->next->content);
			tmp_node = tmp_node->next->next;
		}
		else
			tmp_node = tmp_node->next;
	}
}

static void	crawl_ast(t_ms_ast *ms_ast)
{
	if (ms_ast->left_node && ms_ast->type == PIPE)
		crawl_ast(ms_ast->left_node);
	if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
		here_doc_set_table(ms_ast->right_node);
	if (ms_ast->cmd_info_list)
		here_doc_set_table(ms_ast);
	return ;
}

void	here_doc_set(t_ms_ast *ms_ast)
{
	crawl_ast(ms_ast);
	init_signal(SIGQUIT, sigquit_after_rl); // here docが終わったらまた元のルールに設定する
}
