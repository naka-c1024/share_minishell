/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_set_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:57:22 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/24 14:03:08 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static bool	is_valid_start_file(char *file_name)
{
	if (access(file_name, R_OK) == 0)
		return (true);
	return (false);
}

void	sb_set_heredoc(t_ms_ast *ast_node, t_process_info *proc_info)
{
	proc_info->hrdc_info = (t_heredoc_info *)ft_calloc(1, sizeof(t_heredoc_info));
	proc_info->hrdc_info->buffer = ast_node->buffer;
	proc_info->is_here_doc = true;
}

void	sb_set_out_file(t_process_info *proc_info, char *file_name, int redirect_type)
{
	//redirect_type 3:> 4:>>
	if (redirect_type == 3)
		proc_info->file_info->out_fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		proc_info->file_info->out_fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
	proc_info->file_info->out_file = true;
}

void	sb_set_in_file(t_process_info *proc_info, char *file_name)
{
	//redirect_type 1:< 2:<<(here_doc)
	if (!file_name)
		;
	if (!is_valid_start_file(file_name))
	{
		safe_func(pipex_putstr("minishell: "), proc_info);
		perror(file_name);
		// free_all_info(info, false, 0);
		exit(EXIT_FAILURE);//親だからexitしちゃうとまずい
	}
	proc_info->file_info->in_file = true;
	proc_info->file_info->in_fd = safe_func(open(file_name, R_OK), proc_info);//safe_funcも親用のやつを作る
	proc_info->is_here_doc = true;
}
