/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:02:03 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/20 00:14:36 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	my_pwd(t_envlist *envlist)
{
	char	*pwd_buf;

	(void)envlist;
	pwd_buf = getcwd(NULL, 0);
	if (pwd_buf == NULL)
	{
		if (errno == ENOENT)
		{
			while (envlist)
			{
				if (my_strcmp("PWD", envlist->key) == 0)
				{
					ft_putendl_fd(envlist->value, STDOUT_FILENO);
					free(pwd_buf);
					return (EXIT_SUCCESS);
				}
				envlist = envlist->next;
			}
		}
		print_error("pwd", NULL, errno);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd_buf, STDOUT_FILENO);
	free(pwd_buf);
	return (EXIT_SUCCESS);
}
