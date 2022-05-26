/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:18:00 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/17 03:28:04 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc_input.h"

static size_t	get_here_doc_init(t_ms_ast *ms_ast, char *delimiter)
{
	size_t	len;
	// char	*new_delimiter;

	ms_ast->buffer = ft_strdup("");
	if (!ms_ast->buffer)
		;// exit(error_handler());
	len = ft_strlen(delimiter);
	ms_ast->delimiter = (char *)ft_calloc(len + 1, sizeof(char));
	ft_strlcpy(ms_ast->delimiter, delimiter, len + 1);
	ms_ast->delimiter[len] = '\n';
	return (len);
}

void	set_here_doc(t_ms_ast *ms_ast, char *delimiter)
{
	size_t	len;
	char	*temp;
	char	*new_document;

	if (!delimiter)
		;
	ms_ast->is_here_doc = true;
	len = get_here_doc_init(ms_ast, delimiter);
	write(1, ">", 1);
	temp = get_next_line(0);
	if (!temp)
		;// exit(error_handler());
	while (ft_strncmp(temp, ms_ast->delimiter, len + 1))
	{
		new_document = ft_strjoin(ms_ast->buffer, temp);
		if (!new_document)
		{
			free(temp);
			;// exit(free_all_info(proc_info, true, 1));
		}
		free(ms_ast->buffer);
		free(temp);
		ms_ast->buffer = new_document;
		write(1, ">", 1);
		temp = get_next_line(0);
	}
	free(temp);
}

static void	here_doc_set_table(t_ms_ast *cmd_node)
{
	// int	here_doc_count;

	// here_doc_count = here_doc_counter(cmd_node->cmd_info_list);
	// if (here_doc_count == 0)
	// 	return ;
	// cmd_node->buffer = (char **)ft_calloc(here_doc_count + 1, sizeof(char *));
	// cmd_node->delimiter = (char **)ft_calloc(here_doc_count + 1, sizeof(char *));
	t_list	*tmp_node;

	tmp_node = cmd_node->cmd_info_list;
	while (tmp_node)
	{
		if (!ft_strncmp(tmp_node->content, "<<", 2))
		{
			set_here_doc(cmd_node, tmp_node->next->content);
			tmp_node = tmp_node->next->next;
		}
		else
		{
			tmp_node = tmp_node->next;
		}
	}
}

static void crawl_ast(t_ms_ast *ms_ast)
{
	if (ms_ast->left_node && ms_ast->type == PIPE)
		crawl_ast(ms_ast->left_node);
	if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
	{
		here_doc_set_table(ms_ast->right_node);
	}
	if (ms_ast->cmd_info_list)
		here_doc_set_table(ms_ast);
	return ;
}

void	here_doc_set(t_ms_ast *ms_ast)
{
	crawl_ast(ms_ast);
}
