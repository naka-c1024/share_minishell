/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_set_env_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:13:52 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/17 16:16:24 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

bool	can_export(char *str)
{
	size_t	i;

	if (ft_isdigit(str[0]))
		return (false);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ('#' <= str[i] && str[i] <= '/')
			return (false);
		else if (str[i] == ':' || str[i] == '?' || str[i] == '@')
			return (false);
		else if ('[' <= str[i] && str[i] <= '^')
			return (false);
		i++;
	}
	return (true);
}

bool	is_equal(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	is_env_key(char *str, t_envlist *envlist)
{
	size_t	len;

	len = ft_strlen(str);
	while (envlist)
	{
		if (ft_strncmp(str, envlist->key, len + 1) == 0)
			return (true);
		envlist = envlist->next;
	}
	return (false);
}

int	no_equal(char *str, t_envlist **envlist)
{
	t_envlist	*newlist;

	if (is_env_key(str, *envlist) == true)
	{
		return (0);
	}
	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
	{
		print_error("export: malloc:", NULL, errno);
		return (1);
	}
	newlist->key = ft_strdup(str);
	newlist->value = NULL;
	newlist->next = NULL;
	ms_lstadd_back(envlist, newlist);
	return (0);
}

void	not_a_valid_identifier(char *str)
{
	ft_putstr_fd("my_shell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
