/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:37:29 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/13 10:14:39 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	here_doc_seqence(t_info *info, t_process_info *proc_info)
{
	size_t	buf_len;

	proc_info->hrdc_info->here_doc_pipe = (int *)ft_calloc(2, sizeof(int));
	pipe(proc_info->hrdc_info->here_doc_pipe);
	dup2(proc_info->hrdc_info->here_doc_pipe[0], STDIN);
	if (proc_info->section == info->process_cnt - 1 || proc_info->file_info->out_file == true)
		dup2(proc_info->file_info->out_fd, STDOUT);//ファイルがあるか最後のプロセスの場合
	else
		dup2(info->pipefd[proc_info->section][1], STDOUT);//どちらでもない場合は次のプロセスの入力に繋ぐ
	buf_len = ft_strlen(proc_info->hrdc_info->buffer);
	write(proc_info->hrdc_info->here_doc_pipe[1], proc_info->hrdc_info->buffer, buf_len);
	if (proc_info->file_info->out_file == true)
		close(proc_info->file_info->out_fd);
	close(proc_info->hrdc_info->here_doc_pipe[0]);
	close(proc_info->hrdc_info->here_doc_pipe[1]);
}

void	child_exe(t_info *info, t_process_info *proc_info, t_ms_ast *ast_node)
{
	proc_info->file_info = (t_file_info *)ft_calloc(1, sizeof(t_file_info));
	if (!proc_info->file_info)
		;
	proc_info->file_info->in_fd = STDIN;
	proc_info->file_info->out_fd = STDOUT;
	redirection_seqence(ast_node, proc_info, info);
	proc_info->cmd = lst_to_arr(proc_info->cmd_list);
	convert_to_cmd_full_path(info, proc_info);
	if (proc_info->is_here_doc == true)
		here_doc_seqence(info, proc_info);
	else
	{
		dup2_func(info, proc_info);
		close_func(info, proc_info);
	}
	execve(proc_info->cmd_full_path, proc_info->cmd, info->envp);
	write (2, "not found command\n", 18);
	exit (127);
	// free_all_info(info, false, 127);
}
