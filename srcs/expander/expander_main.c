/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:52:44 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/19 23:44:59 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	find_meta_char(t_list **cp_list, t_envlist *envlist)
{
	size_t	i;

	i = 0;
	while (((*cp_list)->content)[i])
	{
		if (((*cp_list)->content)[i] == '\'')
		{
			expand_single(&((*cp_list)->content));
			break ;
		}
		if (((*cp_list)->content)[i] == '\"')
		{
			expand_double(&((*cp_list)->content), envlist);
			break ;
		}
		if (((*cp_list)->content)[i] == '$' &&
			((*cp_list)->content)[i + 1] != '\0')
		{
			expand_dollar(&((*cp_list)->content), envlist);
			i = 0;
			continue ;
		}
		i++;
	}
}

static void	send_single_token(t_list **list, t_envlist *envlist)
{
	t_list	**cp_list;

	cp_list = list;
	while (*cp_list)
	{
		find_meta_char(cp_list, envlist);
		cp_list = &((*cp_list)->next);
	}
}

static void	crawl_ast(t_ms_ast **ms_ast, t_envlist *envlist)
{
	if ((*ms_ast)->left_node && (*ms_ast)->type == PIPE)
		crawl_ast(&((*ms_ast)->left_node), envlist);
	if ((*ms_ast)->left_node && (*ms_ast)->left_node->cmd_info_list)
	{
		if ((*ms_ast)->buffer)
			expand_dollar(&((*ms_ast)->buffer), envlist);
		send_single_token(&((*ms_ast)->left_node->cmd_info_list), envlist);
	}
	if ((*ms_ast)->right_node && (*ms_ast)->right_node->cmd_info_list)
	{
		if ((*ms_ast)->buffer)
			expand_dollar(&((*ms_ast)->buffer), envlist);
		send_single_token(&((*ms_ast)->right_node->cmd_info_list), envlist);
	}
	if ((*ms_ast)->cmd_info_list)
	{
		if ((*ms_ast)->buffer)
			expand_dollar(&((*ms_ast)->buffer), envlist);
		send_single_token(&((*ms_ast)->cmd_info_list), envlist);
	}
	return ;
}

bool	expander(t_ms_ast **ms_ast, t_envlist *envlist)
{
	t_envlist	*cp_elist;

	cp_elist = envlist;
	if ((*ms_ast)->cmd_info_list->content[0] == '$')
	{
		while (cp_elist)
		{
			if (my_strcmp((*ms_ast)->cmd_info_list->content + 1, cp_elist->key)
				== 0)
				break ;
			cp_elist = cp_elist->next;
		}
		if (cp_elist == NULL)
		{
			free_ast(*ms_ast);
			return (false);
		}
	}
	crawl_ast(ms_ast, envlist);
	return (true);
}
