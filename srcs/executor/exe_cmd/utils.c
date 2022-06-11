/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:02:25 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/29 15:41:47 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	safe_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_split(char **ptr)
{
	size_t	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	print_error(char *cmd, char *cmd_arg, int error_number)
{
	ft_putstr_fd("my_shell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (cmd_arg)
	{
		ft_putstr_fd(cmd_arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(strerror(error_number), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
