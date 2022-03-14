/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 16:53:38 by ynakashi          #+#    #+#             */
/*   Updated: 2021/08/28 16:26:19 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (('a' <= c && c <= 'z'))
		c = c - ('a' - 'A');
	return (c);
}
/*
#include <stdio.h>
int main(void)
{
	printf("A = %c\n",ft_toupper('a'));
	printf("1 = %c\n",ft_toupper('1'));
	printf("! = %c\n",ft_toupper('!'));
	return 0;
}
*/
