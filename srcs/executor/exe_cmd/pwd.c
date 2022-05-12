/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:02:03 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/29 15:41:37 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	my_pwd(void)
{
	char	*pwd_buf;

	pwd_buf = getcwd(NULL, 0);
	if (pwd_buf == NULL)
	{
		print_error("pwd", NULL, errno);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(pwd_buf, STDOUT_FILENO);
	free(pwd_buf);
	return (EXIT_SUCCESS);
}
