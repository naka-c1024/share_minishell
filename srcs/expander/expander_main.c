/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:52:44 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/12 18:36:03 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_exit_status(char **dollar_str, size_t dollar_loc)
{
	char	*pre_dollar_str;
	char	*post_dollar_str;
	size_t	post_size;
	char	*dollar;
	char	*tmp;

	post_size = ft_strlen(*dollar_str + dollar_loc + 2);
	pre_dollar_str = ft_x_substr(*dollar_str, 0, dollar_loc);
	post_dollar_str = ft_x_substr(*dollar_str, dollar_loc + 2, post_size);
	dollar = ft_x_itoa(g_exit_status);
	free(*dollar_str);
	tmp = ft_x_strjoin(pre_dollar_str, dollar);
	*dollar_str = ft_x_strjoin(tmp, post_dollar_str);
	free(pre_dollar_str);
	free(post_dollar_str);
	free(dollar);
	free(tmp);
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
				expand_exit_status(str, i);
			}
			else
			{
				expand_env_var(str, envlist);
				// 前後に文字があってもしっかり展開できるようになったらi = 0;にした方がいいかも
			}
		}
		i++;
	}
}

static size_t	count_quote(char *str, int c)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
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
	size_t	quote_cnt;

	quote_cnt = count_quote(*str, '\'');
	ptr = (char *)malloc(sizeof(char) * ft_strlen(*str) - quote_cnt + 1);
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

static void	expand_double(char **str, t_envlist *envlist)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	quote_cnt;

	quote_cnt = count_quote(*str, '\"');
	ptr = (char *)malloc(sizeof(char) * ft_strlen(*str) - quote_cnt + 1);
	i = 0;
	j = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] != '\"')
		{
			ptr[j] = (*str)[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	free(*str);
	*str = ptr;
	expand_dollar(str, envlist);
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
			if (((*cp_list)->content)[i] == '\'') // 最初に'が来たら'だけを処理する
			{
				expand_single(&((*cp_list)->content));
				break ; // single内ではdouble quoteや環境変数展開はしない
			}
			if (((*cp_list)->content)[i] == '\"')
			{
				expand_double(&((*cp_list)->content), envlist); // この中でもdollar展開はする
				break ;
			}
			if (((*cp_list)->content)[i] == '$')
			{
				expand_dollar(&((*cp_list)->content), envlist);
				break ;
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

void	expander(t_ms_ast **ms_ast, t_envlist *envlist)
{
	if (!(*ms_ast))
		return ;
	crawl_ast(ms_ast, envlist);
}
