/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ipc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:51:49 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/28 13:06:07 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_filefd(t_info *info, int cmd_index)
{
	int	fd;

	if (info->file && cmd_index == 0)
	{
		if (!is_valid_start_file(*info))
		{
			safe_func(pipex_putstr("pipex: ", STDERR), info);
			perror(info->argv[1]);
			free_all_info(info, false, 0);
			exit(EXIT_FAILURE);
		}
		fd = safe_func(open(info->file, R_OK), info);
	}
	else if (info->file && cmd_index + info->first_cmd_index == info->argc - 2)
	{
		if (info->is_here_doc == false)
			fd = open(info->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			fd = open(info->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
	}
	else
		fd = NOFILE;
	return (fd);
}

void	dup2_func(t_info *info, int filefd, int cmd_index)
{
	if (filefd != NOFILE && cmd_index == 0)
	{
		safe_func(dup2(filefd, STDIN), info);
		safe_func(dup2(info->pipefd[cmd_index][PIPEOUT], STDOUT), info);
	}
	else if (filefd != NOFILE && \
				cmd_index + info->first_cmd_index == info->argc - 2)
	{
		safe_func(dup2(filefd, STDOUT), info);
		safe_func(dup2(info->pipefd[cmd_index - 1][PIPEIN], STDIN), info);
	}
	else
	{
		safe_func(dup2(info->pipefd[cmd_index - 1][PIPEIN], STDIN), info);
		safe_func(dup2(info->pipefd[cmd_index][PIPEOUT], STDOUT), info);
	}
}

void	close_func(t_info *info, int filefd, int cmd_index)
{
	if (filefd != NOFILE && cmd_index == 0)
		safe_func(close(info->pipefd[cmd_index][PIPEIN]), info);
	else if (filefd != NOFILE && \
			cmd_index + info->first_cmd_index == info->argc - 2)
		safe_func(close(info->pipefd[cmd_index - 1][PIPEOUT]), info);
	else
		safe_func(close(info->pipefd[cmd_index - 1][PIPEOUT]), info);
	if (filefd != NOFILE)
		safe_func(close(filefd), info);
	if (cmd_index + info->first_cmd_index != info->argc - 2)
		safe_func(close(info->pipefd[cmd_index][PIPEOUT]), info);
}
