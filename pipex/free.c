/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:31:29 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/28 12:01:45 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_3arr(void ****arr)
{
	int	i;
	int	j;

	if (!arr || !(*arr))
		return ;
	i = 0;
	while ((*arr)[i])
	{
		j = 0;
		while ((*arr)[i][j])
		{
			free((*arr)[i][j]);
			(*arr)[i][j] = NULL;
			j++;
		}
		free((*arr)[i][j]);
		(*arr)[i][j] = NULL;
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free((*arr)[i]);
	(*arr)[i] = NULL;
	free(*arr);
	*arr = NULL;
}

void	free_2arr(void ***arr)
{
	int	i;

	if (!arr || !(*arr))
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free((*arr)[i]);
	(*arr)[i] = NULL;
	free(*arr);
	*arr = NULL;
}

static void	free_info(t_info *info)
{
	if (!info)
		return ;
	free_2arr((void ***)&(info->pipefd));
	free_2arr((void ***)&(info->cmd_full_path));
	free_3arr((void ****)&(info->cmd_full_path));
	if (info->total_document)
		free(info->total_document);
	info->total_document = NULL;
	if (info->pid)
		free(info->pid);
	info->pid = NULL;
}

int	free_all_info(t_info *info, bool is_error, int error_status)
{
	if (info)
		free_info(info);
	if (is_error)
		return (error_handler());
	exit (error_status);
}
