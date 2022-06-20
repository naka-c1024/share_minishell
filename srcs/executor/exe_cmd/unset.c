/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:02:13 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/20 11:40:11 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_unset(char *key, char *value, void *cp_elist)
{
	free(key);
	free(value);
	free(cp_elist);
}

int	my_unset(char **split_ln, t_envlist **envlist)
{
	size_t		i;
	t_envlist	*tmp;
	size_t		len;
	t_envlist	**cp_elist;

	i = 1;
	while (split_ln[i])
	{
		cp_elist = envlist;
		while (*cp_elist)
		{
			len = ft_strlen(split_ln[i]);
			if (ft_strncmp(split_ln[i], (*cp_elist)->key, len + 1) == 0)
			{
				tmp = (*cp_elist)->next;
				free_unset((*cp_elist)->key, (*cp_elist)->value, *cp_elist);
				*cp_elist = tmp;
				break ;
			}
			cp_elist = &(*cp_elist)->next;
		}
		i++;
	}
	return (0);
}
