/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 04:27:31 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/25 11:03:26 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static bool	cmd_seaching(t_process_info *p_info, char **all_paths)
{
	int		path_index;
	char	*temp;

	path_index = 0;
	while (all_paths[path_index])
	{
		temp = ft_x_strjoin(all_paths[path_index], "/");
		p_info->cmd_full_path = ft_x_strjoin(temp, p_info->cmd[0]);
		free(temp);
		if (!access(p_info->cmd_full_path, X_OK))
			return (true);
		free(p_info->cmd_full_path);
		p_info->cmd_full_path = NULL;
		path_index++;
	}
	return (false);
}

static bool	is_full_path_case(t_process_info *p_info)
{
	if (!access(p_info->cmd[0], X_OK))
	{
		p_info->cmd_full_path = ft_x_strdup(p_info->cmd[0]);
		return (true);
	}
	return (false);
}

static	char	**get_all_paths(t_info *info)
{
	char		**all_paths;
	t_envlist	*role_envlist;

	role_envlist = info->envlist;
	while (role_envlist)
	{
		if (!ft_strncmp(role_envlist->key, "PATH", PATH_PREFIX))
		{
			all_paths = ft_x_split(role_envlist->value, ':');
			return (all_paths);
		}
		role_envlist = role_envlist->next;
	}
	return (NULL);
}

void	convert_to_cmd_full_path(t_info *info, t_process_info *p_info)
{
	char	**all_paths;

	if (is_full_path_case(p_info))
	{
		file_type_check(p_info);
		return ;
	}
	all_paths = get_all_paths(info);
	if (!all_paths)
		p_info->cmd_full_path = ft_x_strdup(p_info->cmd[0]);
	else if (cmd_seaching(p_info, all_paths))
	{
		free_twod_array(all_paths);
		file_type_check(p_info);
	}
	else
	{
		no_such_fileordir(p_info);
		p_info->cmd_full_path = ft_x_strdup(p_info->cmd[0]);
	}
	return ;
}
