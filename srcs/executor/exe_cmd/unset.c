/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:02:13 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/17 15:31:22 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
				free((*cp_elist)->key);
				free((*cp_elist)->value);
				free((*cp_elist));
				*cp_elist = tmp;
				break ;
			}
			cp_elist = &(*cp_elist)->next;
		}
		i++;
	}
	return (0);
}
