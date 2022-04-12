/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:52:44 by ynakashi          #+#    #+#             */
/*   Updated: 2022/04/13 08:07:15 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_exit_status(char **dollar_str)
{
	char	*dollar_ptr;
	// char	*pre_tmp;
	// char	*post_tmp;

	// dollar_ptr = ft_strnstr(*dollar_str, "$?", ft_strlen(*dollar_str));
	free(*dollar_str);
	*dollar_str = ft_itoa(g_exit_status);
}

static void	expand_env_var(char **dollar_str, t_envlist *envlist)
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

static void	expand_dollar(char **str, t_envlist *envlist)
{
	size_t	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((*str)[i + 1] == '?')
			{
				expand_exit_status(str);
			}
			else
			{
				expand_env_var(str, envlist);
			}
		}
		i++;
	}
}

static size_t	count_single(char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str == '\'')
			i++;
		str++;
	}
	return (i);
}

static void	expand_single(char **str)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	single_cnt;

	single_cnt = count_single(*str);
	ptr = (char *)malloc(sizeof(char) * ft_strlen(*str) - single_cnt + 1);
	i = 0;
	j = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] != '\'')
		{
			ptr[j] = (*str)[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	free(*str);
	*str = ptr;
}

static void	expand_double(char **str)
{
	printf("double quote\n");
}

static void	send_single_token(t_list **list, t_envlist *envlist)
{
	t_list	**cp_list;
	size_t	i;

	cp_list = list;
	while (*cp_list)
	{
		i = 0;
		while (((*cp_list)->content)[i])
		{
			if (((*cp_list)->content)[i] == '\'')
			{
				expand_single(&((*cp_list)->content));
				break ; // single内ではdouble quoteや環境変数展開はしない
			}
			if (((*cp_list)->content)[i] == '\"')
			{
				expand_double(&((*cp_list)->content));
			}
			if (((*cp_list)->content)[i] == '$')
			{
				expand_dollar(&((*cp_list)->content), envlist);
			}
			i++;
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
