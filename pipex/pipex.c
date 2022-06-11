/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 22:33:07 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/28 14:05:33 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	get_here_doc_init(t_info *info)
{
	size_t	len;

	info->total_document = ft_strdup("");
	if (!info->total_document)
		exit(error_handler());
	len = ft_strlen(info->limiter);
	info->limiter[len] = '\n';
	return (len);
}

static void	get_here_doc(t_info *info)
{
	size_t	len;
	char	*temp;
	char	*new_document;

	len = get_here_doc_init(info);
	temp = get_next_line(0);
	if (!temp)
		exit(error_handler());
	while (ft_strncmp(temp, info->limiter, len + 1))
	{
		new_document = ft_strjoin(info->total_document, temp);
		if (!new_document)
		{
			free(temp);
			exit(free_all_info(info, true, 1));
		}
		free(info->total_document);
		free(temp);
		info->total_document = new_document;
		temp = get_next_line(0);
	}
	free(temp);
}

static void	init_info2(t_info *info)
{
	int	process_cnt;
	int	i;

	process_cnt = info->argc - 3 - info->is_here_doc;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * process_cnt);
	if (!info->pid)
		exit(free_all_info(info, true, 1));
	info->pipefd = (int **)malloc(sizeof(int *) * (process_cnt));
	if (!info->pipefd)
		exit(free_all_info(info, true, 1));
	info->pipefd[process_cnt - 1] = NULL;
	info->cmd_full_path = (char **)malloc(sizeof(char *) * (process_cnt + 1));
	if (!info->cmd_full_path)
		exit(free_all_info(info, true, 1));
	i = 0;
	while (i <= process_cnt)
		info->cmd_full_path[i++] = NULL;
	info->cmd = (char ***)malloc(sizeof(char **) * (process_cnt + 1));
	if (!info->cmd)
		exit(free_all_info(info, true, 1));
	info->cmd[process_cnt] = NULL;
}

void	init_info1(t_info *info, int ac, char **av, char **ep)
{
	info->argv = av;
	info->argc = ac;
	if (!ep)
		exit(error_handler());
	info->envp = ep;
	info->error_status = 0;
	info->is_here_doc = false;
	info->total_document = NULL;
	info->cmd_full_path = NULL;
	info->pid = NULL;
	info->pipefd = NULL;
	info->cmd = NULL;
	if (ac < 5)
		exit(error_handler());
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		if (ac < 6)
			exit(error_handler());
		info->is_here_doc = true;
		info->limiter = av[2];
		get_here_doc(info);
	}
	info->first_cmd_index = 2 + info->is_here_doc;
	info->process_cnt = ac - 3 - info->is_here_doc;
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;
	int			i;

	init_info1(&info, argc, argv, envp);
	init_info2(&info);
	i = 0;
	while (i < info.process_cnt - 1)
	{
		info.pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (!info.pipefd[i])
			exit(free_all_info(&info, true, 1));
		i++;
	}
	info.error_status = start_process(info);
	free_all_info(&info, false, info.error_status);
}
