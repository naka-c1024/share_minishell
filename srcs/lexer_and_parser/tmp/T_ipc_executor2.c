/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_executor2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:51:49 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/24 12:20:58 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

int	safe_func(int res, t_info *info)
{
	if (res == -1)
	{
		// free_all_info(info, true, 1);
		exit(1);
	}
	return (res);
}

// int	get_filefd(t_info *info, int p_info->section)
// {
// 	int	fd;

// 	if (info->file && p_info->section == 0)
// 	{
// 		if (!is_valid_start_file(*info))
// 		{
// 			safe_func(pipex_putstr("pipex: ", STDERR), info);
// 			perror(info->argv[1]);
// 			free_all_info(info, false, 0);
// 			exit(EXIT_FAILURE);
// 		}
// 		fd = safe_func(open(info->file, R_OK), info);
// 	}
// 	else if (info->file && p_info->section + info->first_cmd_index == info->argc - 2)
// 	{
// 		if (info->is_here_doc == false)
// 			fd = open(info->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 		else
// 			fd = open(info->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
// 	}
// 	else
// 		fd = NOFILE;
// 	return (fd);
// }

void	dup2_func(t_info *info, t_process_info *p_info, int filefd)
{
	// printf("%d:%d\n", info->process_cnt, p_info->section);
	if (p_info->section == 0)
	{
		safe_func(dup2(info->pipefd[p_info->section][PIPEIN], STDIN), info);
		safe_func(dup2(info->pipefd[p_info->section][PIPEOUT], STDOUT), info);
	}
	else if (p_info->section == info->process_cnt - 1)
	{
		// printf("ipc_executor2.c/cul_61:%s\n", p_info->cmd_full_path);
		// safe_func(dup2(info->pipefd[p_info->section][PIPEOUT], STDOUT), info);
		safe_func(dup2(info->pipefd[p_info->section - 1][PIPEIN], STDIN), info);
	}
	else
	{
		// printf("ipc_executor2.c/cul_66:%s\n", p_info->cmd_full_path);
		safe_func(dup2(info->pipefd[p_info->section - 1][PIPEIN], STDIN), info);
		safe_func(dup2(info->pipefd[p_info->section][PIPEOUT], STDOUT), info);
	}
}

void	close_func(t_info *info, t_process_info *p_info, int filefd)
{
	if (p_info->section == 0)
		safe_func(close(info->pipefd[p_info->section][PIPEIN]), info);//STDINにPIPEINを割り当ててあるので閉じてよし
	// else if (p_info->section == info->process_cnt)
	// 	safe_func(close(info->pipefd[p_info->section - 1][PIPEOUT]), info);
	if (p_info->section != 0)
		safe_func(close(info->pipefd[p_info->section - 1][PIPEOUT]), info);
	if (filefd != NOFILE)
		safe_func(close(filefd), info);//dupで標準入力を割り当ててるからこっちは使わない
	if (p_info->section == info->process_cnt - 1)
	{
		// printf("ipc_executor2.c/86:running\n");
		// safe_func(close(info->pipefd[p_info->section][PIPEOUT]), info);
	}
}
