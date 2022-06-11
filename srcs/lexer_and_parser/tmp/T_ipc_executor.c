/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:37:29 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/26 03:59:08 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

void	child_exe(t_info *info, t_process_info *p_info)
{
	int	filefd;
	int	total_len;

	// if (info->is_here_doc == true && cmd_index == 0)
	// {
	// 	total_len = ft_strlen(info->total_document);
	// 	safe_func(close(info->pipefd[0][0]), info);
	// 	safe_func \
	// 		(write(info->pipefd[0][1], info->total_document, total_len), info);
	// 	safe_func(close(info->pipefd[0][1]), info);
	// 	exit(EXIT_SUCCESS);
	// }
	// filefd = get_filefd(info, cmd_index);
	// if (filefd == -1)
	// {
	// 	perror(info->file);
	// 	free_all_info(info, false, 1);
	// 	exit(EXIT_SUCCESS);
	// }
	filefd = NOFILE;
	dup2_func(info, p_info, filefd);
	redirection_seqence(p_info);
	close_func(info, p_info, filefd);
	execve(p_info->cmd_full_path, p_info->cmd, info->envp);
	write (2, "not found command\n", 18);
	exit (127);
	// free_all_info(info, false, 127);
}

// static void	set_elements(t_info *info, int cmd_index)
// {
// 	info->file = NULL;
// 	if (cmd_index == 0 && !info->is_here_doc)
// 		info->file = info->argv[1];
// 	else if (cmd_index == info->process_cnt - 1)
// 		info->file = info->argv[info->argc - 1];
// 	info->cmd[cmd_index] = \
// 			ft_split(info->argv[info->first_cmd_index + cmd_index], ' ');
// 	if (!info->cmd[cmd_index])
// 		exit(free_all_info(info, true, 1));
// 	convert_to_cmd_full_path(info, cmd_index);
// }

// static void	deploy_process(t_info *info)
// {
// 	int	cmd_index;

// 	cmd_index = 0;
// 	while (cmd_index < info->process_cnt)
// 	{
// 		set_elements(info, cmd_index);
// 		if (cmd_index + 1 != info->process_cnt && \
// 					pipe(info->pipefd[cmd_index]) < 0)
// 			exit(free_all_info(info, true, 1));
// 		info->pid[cmd_index] = fork();
// 		if (info->pid[cmd_index] == -1)
// 			exit(free_all_info(info, true, 1));
// 		else if (info->pid[cmd_index] == 0)
// 			child_exe(info, cmd_index);
// 		else
// 		{
// 			if (cmd_index != 0)
// 			{
// 				safe_func(close(info->pipefd[cmd_index - 1][0]), info);
// 				safe_func(close(info->pipefd[cmd_index - 1][1]), info);
// 			}
// 		}
// 		cmd_index++;
// 	}
// }

// int	start_process(t_info info)
// {
// 	int	wstatus;
// 	int	cmd_index;

// 	deploy_process(&info);
// 	cmd_index = 0;
// 	while (cmd_index < info.process_cnt)
// 	{
// 		safe_func(waitpid(info.pid[cmd_index], &wstatus, WUNTRACED), &info);
// 		cmd_index++;
// 	}
// 	return (WEXITSTATUS(wstatus));
// }
