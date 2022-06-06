/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin_executor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:38:15 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/03 17:17:01 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	according_to_cmd(int cmd_type, \
			char **plain_cmd, t_envlist **envlist)
{
	if (cmd_type == MY_EXIT)
		g_exit_status = my_exit(plain_cmd);
	else if (cmd_type == MY_ECHO)
		g_exit_status = my_echo(plain_cmd);
	else if (cmd_type == MY_CD)
		g_exit_status = my_cd(plain_cmd, envlist);
	else if (cmd_type == MY_PWD)
		g_exit_status = my_pwd();
	else if (cmd_type == MY_UNSET)
		g_exit_status = my_unset(plain_cmd, envlist);
	else if (cmd_type == MY_ENV)
		g_exit_status = my_env(*envlist);
	else
		g_exit_status = my_export(plain_cmd, envlist);
}

static void	single_builtin_only(t_ms_ast *ms_ast, \
			t_envlist **envlist, int cmd_type)
{
	char			**plain_cmd;
	t_process_info	*proc_info;
	bool			is_success;

	is_success = true;
	proc_info = serch_redirection(ms_ast, &is_success);
	if (is_success)
	{
		dup_and_close(proc_info);
		plain_cmd = lst_to_arr(proc_info->cmd_list);
		according_to_cmd(cmd_type, plain_cmd, envlist);
		restore_redirection(proc_info);
		free_twod_array(plain_cmd);
	}
	free_ast(ms_ast);
	free_process_info(&proc_info);
}

bool	only_builtin_assign_func(char builtin_list[7][7], \
		t_ms_ast *ms_ast, char *cmd_name, t_envlist **envlist)
{
	int	idx;

	idx = 0;
	while (idx < 7)
	{
		if (!ft_strncmp(cmd_name, builtin_list[idx], 7))
		{
			single_builtin_only(ms_ast, envlist, idx);
			return (true);
		}
		idx++;
	}
	return (false);
}
