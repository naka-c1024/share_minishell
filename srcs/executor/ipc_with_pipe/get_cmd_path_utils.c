/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 11:02:55 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/25 11:03:18 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	file_type_check(t_process_info *p_info)
{
	struct stat	*buf;

	buf = (struct stat *)x_malloc(sizeof(struct stat));
	safe_func(stat(p_info->cmd_full_path, buf));
	if (S_ISDIR(buf->st_mode))
	{
		ft_putstr_fd("my_shell: ", STDERR);
		ft_putstr_fd(p_info->cmd_list->content, STDERR);
		ft_putstr_fd(": is a directory\n", STDERR);
		exit(126);
	}
}

void	no_such_fileordir(t_process_info *p_info)
{
	size_t	idx;

	idx = 0;
	if (ft_strchr(p_info->cmd_list->content, '/'))
	{
		ft_putstr_fd("my_shell: ", STDERR);
		ft_putstr_fd(p_info->cmd_list->content, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		exit(127);
	}
}
