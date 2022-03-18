/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 15:47:22 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/17 21:47:29 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (040 <= c && c <= 0176);
}
// man isprint : note(octal number) -> decimal number(32~126)
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n",ft_isprint('!'));
	printf("%d\n",ft_isprint(127));
	return (0);
}
*/
