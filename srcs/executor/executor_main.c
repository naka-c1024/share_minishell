/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:57:25 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/29 15:33:55 by ynakashi         ###   ########.fr       */
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

void	executor(t_list *cmd_list, t_envlist **envlist)
{
	char	**two_dim_arr;

	two_dim_arr = lst_to_arr(cmd_list);
	if (!two_dim_arr)
	{
		;
	}
	// ft_lstclear(&cmd_list, NULL); // ここでfreeしていいですかね？

	// パイプやリダイレクトの処理の中でonly_one_cmd使う
	g_exit_status = only_one_cmd(two_dim_arr, envlist);
}
