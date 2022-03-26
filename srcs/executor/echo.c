/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:57:12 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/25 19:57:18 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	safe_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (write(fd, s, len) == -1)
	{
		print_error("echo: write", s, errno);
		return (1);
	}
	return (0);
}

static int	echo_main(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (safe_putstr_fd(str[i], STDOUT_FILENO))
			return (1);
		if (str[i + 1])
			if (safe_putstr_fd(" ", STDOUT_FILENO))
				return (1);
		i++;
	}
	return (0);
}

int	my_echo(char **split_ln)
{
	int		display_return;
	size_t	i;

	display_return = 1;
	i = 0;
	if (split_ln[++i] == NULL) // listの最後がnull埋めされている前提
	{
		if (safe_putstr_fd("\n", STDOUT_FILENO))
			return (1);
		return (0);
	}
	if (ft_strncmp(split_ln[i], "-n", 3) == 0)
	{
		display_return = 0;
		i++;
	}
	if (echo_main(&split_ln[i]) == 1)
		return (1);
	if (display_return)
		if (safe_putstr_fd("\n", STDOUT_FILENO))
			return (1);
	return (0);
}
