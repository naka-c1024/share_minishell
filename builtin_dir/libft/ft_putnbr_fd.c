/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:59:20 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/21 15:26:16 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	lnb;
	int		i;
	char	c[10];

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		lnb = (long)n * -1;
	}
	else
		lnb = n;
	i = 0;
	while (lnb > 0)
	{
		c[i++] = lnb % 10 + '0';
		lnb = lnb / 10;
	}
	while (--i >= 0)
		ft_putchar_fd(c[i], fd);
}
// subject -> External functs. write
// This issue prohibits malloc, so you can't use ft_itoa.
// nm -u -> Forbidden function flag
/*
int	main(void)
{
	ft_putnbr_fd(42, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	ft_putnbr_fd(-42, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	ft_putnbr_fd(INT_MAX, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	ft_putnbr_fd(INT_MIN, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	ft_putnbr_fd(0, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
 */
