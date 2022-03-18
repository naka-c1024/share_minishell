/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:57:42 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/21 15:19:07 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	size_t	i;

	if (!s)
		return ;
	len = ft_strlen(s);
	i = 0;
	if (len < INT_MAX)
		write(fd, s, len);
	else
		while (i < len)
			write(fd, &s[i++], sizeof(char));
}
// INT_MAX
// NULL guard!
// ./a.out > file.txt
// wc file.txt
// If INT_MAX is supported, the actions will not end immediately.
/*
int	main(void)
{
	ft_putstr_fd("42tokyo", STDOUT_FILENO);

	// char	*str = malloc((size_t)INT_MAX + 10);
	// ft_memset(str, 'A', (size_t)INT_MAX + 9);
	// str[(size_t)INT_MAX + 9] = '\0';
	// ft_putstr_fd(str, STDOUT_FILENO);
	return (0);
}
 */
