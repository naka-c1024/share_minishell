/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:37:29 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/06 19:41:58 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	here_doc_seqence(t_info *info, t_process_info *proc_info)
{
	size_t	buf_len;

	proc_info->hrdc_info->here_doc_pipe = (int *)ft_x_calloc(2, sizeof(int));
	safe_func(pipe(proc_info->hrdc_info->here_doc_pipe));
	safe_func(dup2(proc_info->hrdc_info->here_doc_pipe[0], STDIN));
	if (proc_info->section == info->process_cnt - 1 || proc_info->file_info->out_file == true)
		safe_func(dup2(proc_info->file_info->out_fd, STDOUT));//ファイルがあるか最後のプロセスの場合
	else
		safe_func(dup2(info->pipefd[proc_info->section][1], STDOUT));//どちらでもない場合は次のプロセスの入力に繋ぐ
	buf_len = ft_strlen(proc_info->hrdc_info->buffer);
	safe_func(write(proc_info->hrdc_info->here_doc_pipe[1], proc_info->hrdc_info->buffer, buf_len));
	if (proc_info->file_info->out_file == true)
		safe_func(close(proc_info->file_info->out_fd));
	safe_func(close(proc_info->hrdc_info->here_doc_pipe[0]));
	safe_func(close(proc_info->hrdc_info->here_doc_pipe[1]));
}

int	case_of_command_not_found(char *cmd_name)
{
	size_t	len;

	len = ft_strlen(cmd_name);
	safe_func(write(2, "minishell: ", 11));
	safe_func(write(2, cmd_name, len));
	safe_func(write (2, ": command not found\n", 20));
	return (127);
}

void	child_exe(t_info *info, t_process_info *proc_info, t_ms_ast *ast_node)
{
	proc_info->file_info = (t_file_info *)ft_x_calloc(1, sizeof(t_file_info));
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
	exit (case_of_command_not_found(proc_info->cmd[0]));
}
