/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_executor2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:51:49 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/12 12:48:19 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	safe_func(int res, void *info)//もとは(int res, t_info *info)
{
	if (res == -1)
	{
		// free_all_info(info, true, 1);
		exit(1);
	}
	return (res);
	 info = NULL;//unused回避用
}

static int	is_some_redirect(char *one_token)
{
	if (!ft_strncmp(one_token, "<<", 2))
		return (2);
	else if (!ft_strncmp(one_token, ">>", 2))
		return (4);
	if (!ft_strncmp(one_token, "<", 1))
		return (1);
	else if (!ft_strncmp(one_token, ">", 1))
		return (3);
	return (0);
}

static ssize_t	pipex_putstr(char *s)
{
	ssize_t	res;

	res = 0;
	if (s == NULL)
		return (-1);
	while (*s && res != -1)
		res = write(STDERR, s++, 1);
	return (res);
}

static bool	is_valid_start_file(char *file_name)
{
	if (access(file_name, R_OK) == 0)
		return (true);
	return (false);
}

static void	set_heredoc(t_ms_ast *ast_node, t_process_info *proc_info, char *delimiter)
{
	delimiter = NULL;//unused回避
	proc_info->hrdc_info = (t_heredoc_info *)ft_calloc(1, sizeof(t_heredoc_info));
	proc_info->hrdc_info->buffer = ast_node->buffer;
	proc_info->is_here_doc = true;
}

void	set_in_file(t_process_info *proc_info, char *file_name)
{
	//redirect_type 1:< 2:<<(here_doc)
	if (!file_name)
		;
	if (!is_valid_start_file(file_name))
	{
		safe_func(pipex_putstr("minishell: "), proc_info);
		perror(file_name);
		// free_all_info(info, false, 0);
		exit(EXIT_FAILURE);
	}
	proc_info->file_info->in_file = true;
	proc_info->file_info->in_fd = safe_func(open(file_name, R_OK), proc_info);
	proc_info->is_here_doc = false;
}

void	set_out_file(t_process_info *proc_info, char *file_name, int redirect_type)
{
	//redirect_type 3:> 4:>>
	if (redirect_type == 3)
		proc_info->file_info->out_fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		proc_info->file_info->out_fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0644);
	proc_info->file_info->out_file = true;
}

void	redirection_seqence(t_ms_ast *ast_node, t_process_info *proc_info, t_info *info)
{
	int	redirect_type;
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
				set_heredoc(ast_node, proc_info, list->next->content);
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
	if (redirect_type == 999)
		info = NULL;//unused
}

void	dup2_func(t_info *info, t_process_info *proc_info)
{
	safe_func(dup2(proc_info->file_info->in_fd, STDIN), info);
	safe_func(dup2(proc_info->file_info->out_fd, STDOUT), info);
	if (proc_info->section == 0)
	{
		if (info->process_cnt != 1 && proc_info->file_info->out_file == false)//一つのみの場合は子プロ手前でpipe関数走ってないのでこれは走ってたら
		{
			safe_func(dup2(info->pipefd[proc_info->section][PIPEOUT], STDOUT), proc_info);
		}
	}
	else if (proc_info->section == info->process_cnt - 1)
	{
		// printf("runnig270\n");
		if (proc_info->file_info->in_file == false)
		{
			safe_func(dup2(info->pipefd[proc_info->section - 1][PIPEIN], STDIN), proc_info);
		}
	}
	else
	{
		if (proc_info->file_info->in_file == false)
		{
			safe_func(dup2(info->pipefd[proc_info->section - 1][PIPEIN], STDIN), proc_info);
		}
		if (proc_info->file_info->out_file == false)
		{
			safe_func(dup2(info->pipefd[proc_info->section][PIPEOUT], STDOUT), proc_info);
		}
	}
}

void	close_func(t_info *info, t_process_info *proc_info)
{
	if (info->process_cnt != 1)
	{
		if (proc_info->section != 0)
		{
			safe_func(close(info->pipefd[proc_info->section - 1][PIPEIN]), proc_info);
			safe_func(close(info->pipefd[proc_info->section - 1][PIPEOUT]), proc_info);
		}
		// safe_func(close(info->pipefd[proc_info->section][PIPEIN]), proc_info);
	}
	if (proc_info->file_info->in_file == true)
	{
		safe_func(close(proc_info->file_info->in_fd), proc_info);
		if (proc_info->section != info->process_cnt - 1)//下のif文と同じように、最後のプロセスに関してはpipeが作られないためこれを消すとcalloc初期化した0(標準入力が閉じちゃう)
			safe_func(close(info->pipefd[proc_info->section][PIPEIN]), proc_info);
	}
	if (proc_info->file_info->out_file == true)
	{
		safe_func(close(proc_info->file_info->out_fd), proc_info);
		if (proc_info->section != info->process_cnt - 1)
			safe_func(close(info->pipefd[proc_info->section][PIPEOUT]), proc_info);
	}
}
