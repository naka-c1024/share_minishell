/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_lst_to_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 15:47:04 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/17 15:50:00 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static size_t	list_cnt(t_envlist *envlist)
{
	size_t	i;

	i = 0;
	while (envlist)
	{
		envlist = envlist->next;
		i++;
	}
	return (i);
}

static int	lst_to_arr3(t_envlist **envlist, size_t *key_len, size_t *value_len)
{
	if (ft_strncmp((*envlist)->key, "_", 2) == 0)
	{
		(*envlist) = (*envlist)->next;
		return (1);
	}
	*key_len = ft_strlen((*envlist)->key);
	if ((*envlist)->value == NULL)
		*value_len = 0;
	else
		*value_len = ft_strlen((*envlist)->value);
	return (0);
}

static int	lst_to_arr4(size_t *i, char **rtn,
	t_envlist **envlist, size_t key_len)
{
	ft_strlcpy(rtn[*i], "declare -x ", 11 + 1);
	ft_strlcat(rtn[*i], (*envlist)->key, 11 + key_len + 1);
	if ((*envlist)->value == NULL)
	{
		(*envlist) = (*envlist)->next;
		(*i)++;
		return (1);
	}
	return (0);
}

static char	**lst_to_arr2(char **rtn, t_envlist *envlist)
{
	size_t			i;
	size_t			key_len;
	size_t			value_len;

	i = 0;
	while (envlist)
	{
		if (lst_to_arr3(&envlist, &key_len, &value_len) == 1)
			continue ;
		rtn[i] = (char *)malloc(key_len + value_len + 14 + 1);
		if (!rtn[i])
		{
			print_error("export: malloc", NULL, errno);
			return (NULL);
		}
		if (lst_to_arr4(&i, rtn, &envlist, key_len) == 1)
			continue ;
		ft_strlcat(rtn[i], "=\"", 11 + key_len + 2 + 1);
		ft_strlcat(rtn[i], envlist->value, 11 + key_len + 2 + value_len + 1);
		ft_strlcat(rtn[i], "\"", 11 + key_len + 2 + value_len + 1 + 1);
		envlist = envlist->next;
		i++;
	}
	rtn[i] = NULL;
	return (rtn);
}

char	**list_to_darray(t_envlist *envlist)
{
	char			**rtn;
	size_t			list_size;

	list_size = list_cnt(envlist);
	list_size -= 1;
	rtn = malloc(sizeof(char *) * (list_size) + 1);
	if (!rtn)
	{
		print_error("export: malloc", NULL, errno);
		return (NULL);
	}
	return (lst_to_arr2(rtn, envlist));
}
