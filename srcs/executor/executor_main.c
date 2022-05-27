/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:57:25 by ynakashi          #+#    #+#             */
/*   Updated: 2022/05/24 13:31:44 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	make_builtin_list(char builtin_list[7][7])
{
	ft_strlcpy(builtin_list[0], "exit", 5);
	ft_strlcpy(builtin_list[1], "echo", 5);
	ft_strlcpy(builtin_list[2], "cd", 3);
	ft_strlcpy(builtin_list[3], "pwd", 4);
	ft_strlcpy(builtin_list[4], "unset", 6);
	ft_strlcpy(builtin_list[5], "env", 4);
	ft_strlcpy(builtin_list[6], "export", 7);
}

void	executor(t_ms_ast *ms_ast, t_envlist **envlist, size_t process_cnt)
{
	char	builtin_list[7][7];
	char	**two_dim_arr;

	if (ms_ast->type == COMMAND)
	{
		make_builtin_list(builtin_list);
		two_dim_arr = lst_to_arr(ms_ast->cmd_info_list);
		if (!only_builtin_assign_func(builtin_list, ms_ast, two_dim_arr[0], envlist))
			g_exit_status = ipc_table(ms_ast, *envlist, process_cnt);
		free_twod_array(two_dim_arr);
	}
	else
		g_exit_status = ipc_table(ms_ast, *envlist, process_cnt);
}
