/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 16:07:13 by ynakashi          #+#    #+#             */
/*   Updated: 2021/08/27 21:45:30 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	unsigned char	*set;

	set = (unsigned char *)buf;
	while (n-- > 0)
		*set++ = (unsigned char)ch;
	return ((void *)buf);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char str[] = "0123456789";

	ft_memset(&str[2], '*', 5);
	printf("%s\n",str);
	memset(&str[2], '*', 5);
	printf("%s\n",str);
	return 0;
}
*/
