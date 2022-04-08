/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:52:44 by ynakashi          #+#    #+#             */
/*   Updated: 2022/04/08 11:06:43 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_exit_status(char **dollar_str)
{
	char	*dollar_ptr;
	// char	*pre_tmp;
	// char	*post_tmp;

	// dollar_ptr = ft_strnstr(*dollar_str, "$?", ft_strlen(*dollar_str));
	free(*dollar_str);
	*dollar_str = ft_itoa(g_exit_status);
}

void	expand_env_var(char **dollar_str, t_envlist *envlist)
{
	while (envlist)
	{
		if (ft_strncmp(&((*dollar_str)[1]), envlist->key, ft_strlen(*dollar_str) + 1) == 0)
		{
			free(*dollar_str);
			*dollar_str = ft_strdup(envlist->value);
		}
		envlist = envlist->next;
	}
}

void	expand_main(char **str, t_envlist *envlist)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '$')
			{
				if (str[i][j + 1] == '?')
				{
					expand_exit_status(&(str[i]));
				}
				else
				{
					expand_env_var(&(str[i]), envlist);
				}
			}
			j++;
		}
		i++;
	}
}

static void send_single_token(t_list **list, t_envlist *envlist)
{
	t_list	**cp_list;

	cp_list = list;
	while (*cp_list)
	{
		if (ft_strchr((*cp_list)->content, '\''))
		{
			printf("single quote\n");
			// シングルクオート展開処理
			cp_list = &((*cp_list)->next);
			continue ; // シングルクオートの中では"と$は展開しない
		}
		if (ft_strchr((*cp_list)->content, '\"'))
		{
			printf("double quote\n");
			// ダブルクオート展開処理
		}
		if (ft_strchr((*cp_list)->content, '$'))
		{
			expand_main(&((*cp_list)->content), envlist);
		}
		cp_list = &((*cp_list)->next);
	}
	return ;
}

static void crawl_ast(t_ms_ast **ms_ast, t_envlist *envlist)
{
	if ((*ms_ast)->left_node && (*ms_ast)->type == PIPE)
		crawl_ast(&((*ms_ast)->left_node), envlist);
	if ((*ms_ast)->left_node && (*ms_ast)->left_node->cmd_info_list)
		send_single_token(&((*ms_ast)->left_node->cmd_info_list), envlist);
	if ((*ms_ast)->right_node && (*ms_ast)->right_node->cmd_info_list)
		send_single_token(&((*ms_ast)->right_node->cmd_info_list), envlist);
	if ((*ms_ast)->cmd_info_list)
		send_single_token(&((*ms_ast)->cmd_info_list), envlist);
	return ;
}

void	expander(t_ms_ast **ms_ast, t_envlist *envlist)
{
	(void)ms_ast; // フラッグ用,削除してください
	(void)envlist; // フラッグ用,削除してください
	if (!(*ms_ast))
		return ;
	crawl_ast(ms_ast, envlist);
}
