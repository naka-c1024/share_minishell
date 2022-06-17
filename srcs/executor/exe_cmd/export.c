/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:01:52 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/17 16:03:40 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	set_new_node(char *str, t_envlist **envlist)
{
	t_envlist	*newlist;
	char		*eq_location;

	newlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (!newlist)
	{
		print_error("export: malloc", NULL, errno);
		return (1);
	}
	eq_location = str;
	while (eq_location && *eq_location != '=')
		eq_location++;
	*eq_location = '\0';
	remove_duplicate(str, envlist);
	newlist->key = ft_strdup(str);
	newlist->value = ft_strdup(++eq_location);
	newlist->next = NULL;
	ms_lstadd_back(envlist, newlist);
	return (0);
}

void	remove_duplicate(char *str, t_envlist **envlist)
{
	t_envlist	**cp_elist;
	t_envlist	*tmp;
	size_t		len;

	cp_elist = envlist;
	while (*cp_elist)
	{
		len = ft_strlen(str);
		if (ft_strncmp(str, (*cp_elist)->key, len + 1) == 0)
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
}

static bool	can_export(char *str)
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

static bool	is_equal(char *str)
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

static int	no_equal(char *str, t_envlist **envlist)
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

static void	not_a_valid_identifier(char *str)
{
	ft_putstr_fd("my_shell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	set_env(char **split_ln, t_envlist **envlist)
{
	size_t	i;
	int		exit_status;

	exit_status = 0;
	i = 0;
	while (split_ln[++i])
	{
		if (can_export(split_ln[i]) == false)
		{
			not_a_valid_identifier(split_ln[i]);
			exit_status = 1;
		}
		else if (is_equal(split_ln[i]) == false)
		{
			if (exit_status == 1)
				no_equal(split_ln[i], envlist);
			else if (exit_status == 0)
				exit_status = no_equal(split_ln[i], envlist);
		}
		else if (exit_status == 1)
			set_new_node(split_ln[i], envlist);
		else if (exit_status == 0)
			exit_status = set_new_node(split_ln[i], envlist);
	}
	return (exit_status);
}

int	my_export(char **split_ln, t_envlist **envlist)
{
	int	exit_status;

	exit_status = 0;
	if (split_ln[1] == NULL)
	{
		print_export(*envlist);
		return (exit_status);
	}
	else
	{
		exit_status = set_env(split_ln, envlist);
	}
	return (exit_status);
}
