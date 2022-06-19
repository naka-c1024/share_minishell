/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:03:22 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/19 22:58:45 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	**bubble_sort(char **darray)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (darray[i])
	{
		j = i + 1;
		while (darray[j])
		{
			if (my_strcmp(darray[i], darray[j]) > 0)
			{
				tmp = darray[i];
				darray[i] = darray[j];
				darray[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (darray);
}

static void	free_darray(char **darray)
{
	size_t	i;

	i = 0;
	while (darray[i])
	{
		free(darray[i]);
		i++;
	}
	free(darray);
}

void	print_export(t_envlist *envlist)
{
	char	**darray;
	size_t	i;

	darray = list_to_darray(envlist);
	if (!darray)
		return ;
	darray = bubble_sort(darray);
	i = 0;
	while (darray[i])
	{
		ft_putendl_fd(darray[i], STDOUT_FILENO);
		i++;
	}
	free_darray(darray);
}
