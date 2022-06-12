/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:30 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 05:20:50 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	small_ipc_table(t_info *info, t_ms_ast *ast_node, int i)
{
	t_process_info	*p_info;

	p_info = (t_process_info *)ft_x_calloc(1, sizeof(t_process_info));
	p_info->section = info->process_cnt - i;
	if (p_info->section + 1 != info->process_cnt)
		safe_func(pipe(info->pipefd[p_info->section]));
	info->pid[p_info->section] = fork();
	if (info->pid[p_info->section] == -1)
		exit (1);
	else if (info->pid[p_info->section] == 0)
		child_exe(info, p_info, ast_node);
	else
	{
		if (p_info->section != 0)
		{
			safe_func(close(info->pipefd[p_info->section - 1][0]));
			safe_func(close(info->pipefd[p_info->section - 1][1]));
		}
	}
	free_process_info(&p_info);
}

static void	crawl_ast_in_ipc_table(t_ms_ast *ms_ast, t_info *info, int i)
{
	if (ms_ast->left_node && ms_ast->type == PIPE)
		crawl_ast_in_ipc_table(ms_ast->left_node, info, ++i);
	if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
	{
		small_ipc_table(info, ms_ast->right_node, i);
	}
	if (ms_ast->cmd_info_list)
	{
		small_ipc_table(info, ms_ast, info->process_cnt);
	}
	return ;
}

int	ipc_table(t_ms_ast *ms_ast, t_envlist *envlist, size_t process_cnt)
{
	t_info	*info;
	int		wstatus;
	int		i;

	info = (t_info *)ft_x_calloc(1, sizeof(t_info));
	info->envlist = envlist;
	info->envp = create_env_arr(envlist);
	info->ms_ast = ms_ast;
	info->process_cnt = process_cnt;
	info->pid = (pid_t *)x_malloc(sizeof(pid_t) * info->process_cnt);
	info->pipefd = (int **)ft_x_calloc(info->process_cnt, sizeof(int *));
	i = 0;
	while (i < info->process_cnt)
		info->pipefd[i++] = (int *)ft_x_calloc(2, sizeof(int));
	crawl_ast_in_ipc_table(ms_ast, info, 0);
	i = 0;
	while (i < info->process_cnt)
	{
		safe_func(waitpid(info->pid[i], &wstatus, WUNTRACED));
		i++;
	}
	free_info(&info);
	return (WEXITSTATUS(wstatus));
}
