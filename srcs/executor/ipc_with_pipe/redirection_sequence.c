/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_sequence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:04:23 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/19 12:13:34 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	set_heredoc(t_ms_ast *ast_node, t_process_info *proc_info)
{
	proc_info->hrdc_info = \
		(t_heredoc_info *)ft_calloc(1, sizeof(t_heredoc_info));
	proc_info->hrdc_info->buffer = ast_node->buffer;
	proc_info->is_here_doc = true;
}

void	set_in_file(t_process_info *proc_info, char *file_name)
{
	safe_func_with_file(access(file_name, R_OK), file_name);
	if (proc_info->file_info->in_file)
		safe_func(close(proc_info->file_info->in_fd));
	proc_info->file_info->in_file = true;
	proc_info->file_info->in_fd = safe_func_with_file \
									(open(file_name, R_OK), file_name);
	proc_info->is_here_doc = false;
}

void	set_out_file(t_process_info *proc_info, \
					char *file_name, int redirect_type)
{
	if (proc_info->file_info->out_file)
		safe_func(close(proc_info->file_info->out_fd));
	if (redirect_type == 3)
		proc_info->file_info->out_fd = safe_func_with_file \
			(open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644), file_name);
	else
		proc_info->file_info->out_fd = safe_func_with_file \
			(open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0644), file_name);
	proc_info->file_info->out_file = true;
}

void	redirection_sequence(t_ms_ast *ast_node, \
							t_process_info *proc_info)
{
	int		redirect_type;
	t_list	*list;

	list = ast_node->cmd_info_list;
	while (list)
	{
		redirect_type = is_some_redirect(list->content);
		if (redirect_type != 0)
		{
			if (redirect_type == 1)
				set_in_file(proc_info, list->next->content);
			else if (redirect_type == 2)
				set_heredoc(ast_node, proc_info);
			else
				set_out_file(proc_info, list->next->content, redirect_type);
			list = list->next;
			if (list)
				list = list->next;
		}
		else
		{
			ft_lstadd_back(&(proc_info->cmd_list), ft_lstnew(list->content));
			list = list->next;
		}
	}
}
