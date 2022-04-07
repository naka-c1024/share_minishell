/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:57:25 by ynakashi          #+#    #+#             */
/*   Updated: 2022/04/07 11:17:51 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_darray(char **darray)
{
	size_t	i;

	i = 0;
	while (darray[i])
	{
		free(darray[i]);
		i++;
	}
	free(darray);
}

static char	**lst_to_arr(t_list *arglst)
{
	char	**rtn;
	size_t	i;
	t_list	*cp_arglst;
	size_t	list_cnt;
	size_t	content_len;

	cp_arglst = arglst;
	list_cnt = 0;
	while (cp_arglst)
	{
		list_cnt++;
		cp_arglst = cp_arglst->next;
	}
	rtn = malloc(sizeof(char *) * (list_cnt) + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arglst)
	{
		content_len = ft_strlen(arglst->content);
		rtn[i] = (char *)malloc(content_len + 1);
		if (!rtn[i])
		{
			perror("malloc");
			free_darray(rtn);
			return (NULL);
		}
		ft_strlcpy(rtn[i], arglst->content, content_len + 1);
		arglst = arglst->next;
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

void	executor(t_ms_ast *ms_ast, t_envlist **envlist)
{
	char	**two_dim_arr;

	two_dim_arr = lst_to_arr(ms_ast->cmd_info_list);
	if (!two_dim_arr)
	{
		;
	}

	// パイプやリダイレクトの処理の中でonly_one_cmd使う
	g_exit_status = only_one_cmd(two_dim_arr, envlist);
}
