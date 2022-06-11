/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast_without_top.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 10:29:06 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/07 11:14:31 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

void	list_clear(t_list *list)
{
	if (list)
	{
		list_clear(list->next);
		free(list->content);
	}
	free(list);
}

void	free_node(t_ms_ast *ms_ast)
{
	if (ms_ast)
	{
		list_clear(ms_ast->cmd_info_list);
		free(ms_ast->delimiter);
		free(ms_ast->buffer);
	}
	free(ms_ast);
}

static void	free_ast_without_top(t_ms_ast *ms_ast)
{
	if (ms_ast->left_node && ms_ast->left_node->left_node)
		free_ast_without_top(ms_ast->left_node);
	free_node(ms_ast->left_node);
	free_node(ms_ast->right_node);
	return ;
}

void	free_ast(t_ms_ast *ms_ast)
{
	free_ast_without_top(ms_ast);
	free_node(ms_ast);
}
