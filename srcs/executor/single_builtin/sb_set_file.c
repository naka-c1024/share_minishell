/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_set_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:57:22 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/08 16:32:41 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static bool	is_valid_file_sb(char *file_name)
{
	if (access(file_name, R_OK) == 0)
		return (true);
	return (false);
}

static bool	put_file_err_msg(char *file_name)
{
	safe_func(write(1, "minishell: ", 11));
	perror(file_name);
	return (false);
}

bool	sb_set_heredoc(t_ms_ast *ast_node, t_process_info *proc_info)
{
	proc_info->hrdc_info = \
		(t_heredoc_info *)ft_x_calloc(1, sizeof(t_heredoc_info));
	proc_info->hrdc_info->buffer = ast_node->buffer;
	proc_info->is_here_doc = true;
	return (true);
}

bool	sb_set_out_file(t_process_info *proc_info, \
						char *file_name, int redirect_type)
{
	int	open_fd;

	if (proc_info->file_info->out_file)
		safe_func(close(proc_info->file_info->out_fd));
	if (redirect_type == OUT)
	{
		open_fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (open_fd == -1)
			return (put_file_err_msg(file_name));
		proc_info->file_info->out_fd = open_fd;
	}
	else
	{
		open_fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (open_fd == -1)
			return (put_file_err_msg(file_name));
		proc_info->file_info->out_fd = open_fd;
	}
	proc_info->file_info->out_file = true;
	return (true);
}

bool	sb_set_in_file(t_process_info *proc_info, char *file_name)
{
	int	open_fd;

	if (!is_valid_file_sb(file_name))
		return (put_file_err_msg(file_name));
	if (proc_info->file_info->in_file)
		safe_func(close(proc_info->file_info->in_fd));
	proc_info->file_info->in_file = true;
	open_fd = open(file_name, O_RDONLY);
	if (open_fd == -1)
		return (put_file_err_msg(file_name));
	proc_info->file_info->in_fd = open_fd;
	proc_info->is_here_doc = true;
	return (true);
}
