/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:14:44 by ynakashi          #+#    #+#             */
/*   Updated: 2021/08/28 16:25:27 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (('A' <= c && c <= 'Z'))
		c = c + ('a' - 'A');
	return (c);
}
/*
#include <stdio.h>
int main(void)
{
	printf("a = %c\n",ft_tolower('a'));
	printf("a = %c\n",ft_tolower('A'));
	printf("! = %c\n",ft_tolower('!'));
	return 0;
}
*/
