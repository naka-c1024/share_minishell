/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:18:00 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/12 16:51:54 by ynakashi         ###   ########.fr       */
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

void	set_here_doc(t_ms_ast *ms_ast, char *delimiter)
{
	size_t	len;
	char	*a_temp;
	char	*b_temp;
	char	*new_document;

	if (!delimiter)
		;
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
