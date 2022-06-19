/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:51:49 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/19 12:17:57 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	dup2_func(t_info *info, t_process_info *p_info)
{
	safe_func(dup2(p_info->file_info->in_fd, STDIN));
	safe_func(dup2(p_info->file_info->out_fd, STDOUT));
	if (p_info->section == 0)
	{
		if (info->process_cnt != 1 && p_info->file_info->out_file == false)
			safe_func(dup2(info->pipefd[p_info->section][PIPEOUT], STDOUT));
	}
	else if (p_info->section == info->process_cnt - 1)
	{
		if (p_info->file_info->in_file == false)
			safe_func(dup2(info->pipefd[p_info->section - 1][PIPEIN], STDIN));
	}
	else
	{
		if (p_info->file_info->in_file == false)
			safe_func(dup2(info->pipefd[p_info->section - 1][PIPEIN], STDIN));
		if (p_info->file_info->out_file == false)
			safe_func(dup2(info->pipefd[p_info->section][PIPEOUT], STDOUT));
	}
}

void	close_func(t_info *info, t_process_info *proc_info)
{
	if (info->process_cnt != 1)
	{
		if (proc_info->section != 0)
		{
			safe_func(close(info->pipefd[proc_info->section - 1][PIPEIN]));
			safe_func(close(info->pipefd[proc_info->section - 1][PIPEOUT]));
		}
	}
	if (proc_info->file_info->in_file == true)
	{
		safe_func(close(proc_info->file_info->in_fd));
		if (proc_info->section != info->process_cnt - 1)
			safe_func(close(info->pipefd[proc_info->section][PIPEIN]));
	}
	if (proc_info->file_info->out_file == true)
	{
		safe_func(close(proc_info->file_info->out_fd));
		if (proc_info->section != info->process_cnt - 1)
			safe_func(close(info->pipefd[proc_info->section][PIPEOUT]));
	}
}
