/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:57:25 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/03 17:15:11 by kahirose         ###   ########.fr       */
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

t_list	*cmd_name_trim(t_list *cmd_info_list)
{
	int				redirect_type;
	t_list			*list;
	t_list			*result_list;

	result_list = NULL;
	list = cmd_info_list;
	while (list)
	{
		redirect_type = is_some_redirect(list->content);
		if (redirect_type != 0)
		{
			list = list->next;
			if (list)
				list = list->next;
		}
		else
		{
			ft_lstadd_back(&result_list, ms_lstnew(list->content));
			list = list->next;
		}
	}
	return (result_list);
}

void	case_of_cmd_not_exist(t_ms_ast *ms_ast, t_list *cmd_name_list)
{
	free_ast(ms_ast);
	list_clear(cmd_name_list);
	g_exit_status = 0;
}

void	executor(t_ms_ast *ms_ast, t_envlist **envlist, size_t process_cnt)
{
	char	builtin_list[7][7];
	t_list	*cmd_name_list;

	if (ms_ast->type == COMMAND)
	{
		make_builtin_list(builtin_list);
		cmd_name_list = cmd_name_trim(ms_ast->cmd_info_list);
		if (!cmd_name_list)
			return (case_of_cmd_not_exist(ms_ast, cmd_name_list));
		if (!only_builtin_assign_func(builtin_list, ms_ast, cmd_name_list->content, envlist))
			g_exit_status = ipc_table(ms_ast, *envlist, process_cnt);
		list_clear(cmd_name_list);
	}
	else
		g_exit_status = ipc_table(ms_ast, *envlist, process_cnt);
}
