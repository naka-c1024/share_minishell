/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 05:12:54 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/20 08:45:01 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static size_t	envlist_len(t_envlist *envlist)
{
	size_t	len;

	len = 0;
	while (envlist)
	{
		len++;
		envlist = envlist->next;
	}
	return (len);
}

char	**create_env_arr(t_envlist *envlist)
{
	char	**env_arr;
	char	*prefix;
	size_t	idx;

	env_arr = (char **)ft_x_calloc(envlist_len(envlist) + 1, sizeof(t_envlist));
	idx = 0;
	while (envlist)
	{
		prefix = ft_x_strjoin(envlist->key, "=");
		env_arr[idx] = ft_x_strjoin(prefix, envlist->value);
		envlist = envlist->next;
		free(prefix);
		idx ++;
	}
	return (env_arr);
}
