/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:01:02 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/29 15:40:59 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	my_env(t_envlist *envlist)
{
	while (envlist)
	{
		if (envlist->value == NULL)
		{
			envlist = envlist->next;
			continue ;
		}
		printf("%s=%s\n", envlist->key, envlist->value);
		envlist = envlist->next;
	}
	return (0);
}
