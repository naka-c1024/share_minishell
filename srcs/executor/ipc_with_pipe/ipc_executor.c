/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:37:29 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/12 14:07:50 by kahirose         ###   ########.fr       */
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
	int	exit_status;

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
	exit_status = EXIT_SUCCESS;
	if (ft_strncmp(proc_info->cmd[0], "exit", 5) == 0)
		exit(exit_status = my_exit(proc_info->cmd));
	else if (ft_strncmp(proc_info->cmd[0], "echo", 5) == 0)
		exit_status = my_echo(proc_info->cmd);
	else if (ft_strncmp(proc_info->cmd[0], "cd", 3) == 0)
		exit(exit_status = my_cd(proc_info->cmd, &(info->envlist)));
	else if (ft_strncmp(proc_info->cmd[0], "pwd", 4) == 0)
		exit(exit_status = my_pwd());
	else if (ft_strncmp(proc_info->cmd[0], "unset", 6) == 0)
		exit(exit_status = my_unset(proc_info->cmd, &(info->envlist)));
	else if (ft_strncmp(proc_info->cmd[0], "env", 4) == 0)
		exit(exit_status = my_env(info->envlist));
	else if (ft_strncmp(proc_info->cmd[0], "export", 7) == 0)
		exit(exit_status = my_export(proc_info->cmd, &(info->envlist)));
	else
	{
		execve(proc_info->cmd_full_path, proc_info->cmd, info->envp);
		write (2, "not found command\n", 18);
		exit (127);
	}
	fprintf(stderr, "end!\n");
	// free_all_info(info, false, 127);
}
