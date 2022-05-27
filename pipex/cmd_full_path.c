/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_full_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:56:49 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/28 12:07:07 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	cmd_seaching(t_info *info, char **all_paths, int cmd_idx)
{
	int		path_index;
	char	*temp;

	path_index = 0;
	while (all_paths[path_index])
	{
		temp = ft_strjoin(all_paths[path_index], "/");
		info->cmd_full_path[cmd_idx] = ft_strjoin(temp, info->cmd[cmd_idx][0]);
		free(temp);
		if (!info->cmd_full_path[cmd_idx])
		{
			free_2arr((void ***)&all_paths);
			exit(free_all_info(info, true, 1));
		}
		if (!access(info->cmd_full_path[cmd_idx], X_OK))
		{
			free_2arr((void ***)&all_paths);
			return (true);
		}
		free(info->cmd_full_path[cmd_idx]);
		info->cmd_full_path[cmd_idx] = NULL;
		path_index++;
	}
	return (false);
}

static	int	get_path_index(t_info info)
{
	int	index;

	index = 0;
	while (info.envp[index])
	{
		if (!ft_strncmp(info.envp[index], "PATH=", PATH_PREFIX))
			return (index);
		index++;
	}
	return (-1);
}

static bool	is_full_path_case(t_info *info, int cmd_index)
{
	if (!access(info->cmd[cmd_index][0], X_OK))
	{
		info->cmd_full_path[cmd_index] = ft_strdup(info->cmd[cmd_index][0]);
		return (true);
	}
	return (false);
}

void	convert_to_cmd_full_path(t_info *info, int cmd_index)
{
	char	**all_paths;
	int		env_index;
	int		path_index;

	if (is_full_path_case(info, cmd_index))
		return ;
	env_index = get_path_index(*info);
	if (env_index == -1)
		exit(free_all_info(info, true, 1));
	all_paths = ft_split(&(info->envp[env_index][PATH_PREFIX]), ':');
	if (!all_paths)
		exit(free_all_info(info, true, 1));
	path_index = 0;
	if (cmd_seaching(info, all_paths, cmd_index))
		return ;
	info->cmd_full_path[cmd_index] = ft_strdup("");
	free_2arr((void ***)&all_paths);
	write(STDERR, "pipex: command not found: ", 26);
	ft_putendl_fd(info->cmd[cmd_index][0], STDERR);
}
