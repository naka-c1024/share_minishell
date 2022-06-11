/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:57:22 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/22 02:48:11 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

ssize_t	pipex_putstr(char *s, int fd)
{
	ssize_t	res;

	res = 0;
	if (s == NULL)
		return (-1);
	while (*s && res != -1)
		res = write(fd, s++, 1);
	return (res);
}

int	error_handler(void)
{
	ft_putstr_fd("Error\n", STDERR);
	return (1);
}
