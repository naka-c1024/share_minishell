/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:52:44 by ynakashi          #+#    #+#             */
/*   Updated: 2022/04/07 11:29:49 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	expand_exit_status(void **str)
// {

// }

// void	expand_env(void **str)
// {
// 	while (**(char **)str != '$')
// 	{
// 		(**(char **)str)++;
// 	}
// 	if (ft_strncmp((char *)(*str), "$?", 2))
// 	{
// 		expand_exit_status(str);
// 	}

// 	*str = "hoge";
// }

static void send_single_token(t_list **list)
{
	t_list	**cp_list;

	cp_list = list;
	while (*cp_list)
	{
		if (ft_strchr((char *)(*cp_list)->content, '\''))
		{
			printf("single quote\n");
			// シングルクオート展開処理
			cp_list = &((*cp_list)->next);
			continue ; // シングルクオートの中では"と$は展開しない
		}
		if (ft_strchr((char *)(*cp_list)->content, '\"'))
		{
			printf("double quote\n");
			// ダブルクオート展開処理
		}
		if (ft_strchr((char *)(*cp_list)->content, '$'))
		{
			printf("environment variables\n");
			// expand_env(&((*cp_list)->content));
		}
		cp_list = &((*cp_list)->next);
	}
	return ;
}

static void crawl_ast(t_ms_ast **ms_ast)
{
	if ((*ms_ast)->left_node && (*ms_ast)->type == PIPE)
		crawl_ast(&((*ms_ast)->left_node));
	if ((*ms_ast)->left_node && (*ms_ast)->left_node->cmd_info_list)
		send_single_token(&((*ms_ast)->left_node->cmd_info_list));
	if ((*ms_ast)->right_node && (*ms_ast)->right_node->cmd_info_list)
		send_single_token(&((*ms_ast)->right_node->cmd_info_list));
	if ((*ms_ast)->cmd_info_list)
		send_single_token(&((*ms_ast)->cmd_info_list));
	return ;
}

static void is_null(t_ms_ast **ms_ast)
{
	if (*ms_ast)
		crawl_ast(ms_ast);
}

void	expander(t_ms_ast **ms_ast, t_envlist *envlist)
{
	(void)ms_ast; // フラッグ用,削除してください
	(void)envlist; // フラッグ用,削除してください
	is_null(ms_ast);
}
