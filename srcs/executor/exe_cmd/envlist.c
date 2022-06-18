/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:01:16 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/17 15:29:01 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_list(t_envlist *list)
{
	t_envlist	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = tmp;
	}
}

static t_envlist	*ms_lstlast(t_envlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ms_lstadd_back(t_envlist **lst, t_envlist *element)
{
	if (!lst || !element)
		return ;
	if (!*lst)
		*lst = element;
	else
		(ms_lstlast(*lst))->next = element;
}

static void	add_oldpwd(t_envlist **envlist)
{
	char	**two_dim_arr;

	two_dim_arr = (char **)x_malloc(sizeof(char *) * 3);
	two_dim_arr[0] = ft_x_strdup("export");
	two_dim_arr[1] = ft_x_strdup("OLDPWD");
	two_dim_arr[2] = NULL;
	my_export(two_dim_arr, envlist);
	free(two_dim_arr[0]);
	free(two_dim_arr[1]);
	free(two_dim_arr);
}

t_envlist	*create_envlist(char **envp)
{
	t_envlist	*head;
	t_envlist	*newlist;
	char		*str;

	head = NULL;
	while (*envp)
	{
		newlist = (t_envlist *)x_malloc(sizeof(t_envlist));
		str = *envp;
		while (*str && *str != '=')
			str++;
		*str = '\0';
		newlist->key = ft_x_strdup(*envp++);
		newlist->value = ft_x_strdup(++str);
		newlist->next = NULL;
		ms_lstadd_back(&head, newlist);
	}
	add_oldpwd(&head);
	return (head);
}
