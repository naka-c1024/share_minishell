/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:57:06 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/06 20:13:15 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

t_ms_ast	*new_pipe_node(t_make_ast_info *ma_info, t_ms_ast *right)
{
	t_ms_ast	*ms_pipe_node;

	ms_pipe_node = (t_ms_ast *)malloc(sizeof(t_ms_ast));
	if (!ms_pipe_node)
		error_occuration_at_make_ast(ma_info, right, true);
	ms_pipe_node->type = PIPE;
	ms_pipe_node->cmd_info_list = NULL;
	ms_pipe_node->left_node = ma_info->ms_ast;
	ms_pipe_node->right_node = right;
	return (ms_pipe_node);
}

static t_list	*make_cmd_list(char ***all_cmd_line, t_make_ast_info *ma_info)
{
	t_list	*new_node;
	t_list	*list;

	list = ft_lstnew(ft_strdup(all_cmd_line[*(ma_info->fir)][*(ma_info->sec)]));
	if (!list)
		error_occuration_at_make_ast(ma_info, NULL, true);
	(*(ma_info->sec))++;
	while (all_cmd_line[*(ma_info->fir)][*(ma_info->sec)] != NULL)
	{
		new_node = ft_lstnew(ft_strdup(all_cmd_line[*(ma_info->fir)][*(ma_info->sec)]));
		if (!new_node)
		{
			list_clear(list);
			error_occuration_at_make_ast(ma_info, NULL, true);
		}
		ft_lstadd_back(&list, new_node);
		(*(ma_info->sec))++;
	}
	*(ma_info->sec) = 0;
	return (list);
}

t_ms_ast	*new_cmd_node(char ***all_cmd_line, t_make_ast_info *ma_info)
{
	t_ms_ast	*ms_cmd_node;

	ms_cmd_node = (t_ms_ast *)malloc(sizeof(t_ms_ast));
	if (!ms_cmd_node)
		error_occuration_at_make_ast(ma_info, NULL, true);
	ms_cmd_node->type = COMMAND;
	ms_cmd_node->cmd_info_list = make_cmd_list(all_cmd_line, ma_info);
	ms_cmd_node->left_node = NULL;
	ms_cmd_node->right_node = NULL;
	(*(ma_info->fir))++;
	return (ms_cmd_node);
}

static bool	is_pipe(char ***all_cmd_line, t_make_ast_info *ma_info)
{
	if (!all_cmd_line[*(ma_info->fir)])
		return (false);
	if ((all_cmd_line)[*(ma_info->fir)][0][0] != '|')
		return (false);
	(*(ma_info->fir))++;
	return (true);
}

void	make_ast_exe(t_make_ast_info **ma_info, char ***all_cmd_line)
{
	char		***tmp_acl;
	t_ms_ast	*ms_ast;

	tmp_acl = all_cmd_line;
	(*ma_info)->ms_ast = new_cmd_node(all_cmd_line, *ma_info);
	while (1)
	{
		if (is_pipe(all_cmd_line, *ma_info))
			(*ma_info)->ms_ast = \
				new_pipe_node(*ma_info, new_cmd_node(all_cmd_line, *ma_info));
		else
			return ;
	}
}
