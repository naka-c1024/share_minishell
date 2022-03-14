/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 12:14:44 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/18 10:37:09 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (d == s || n == 0)
		return (dest);
	if (d < s)
		ft_memcpy(dest, src, n);
	else
	{
		d = &d[n - 1];
		s = &s[n - 1];
		while (n-- > 0)
			*d-- = *s--;
	}
	return ((void *)dest);
}
// not NULL guard
// apple open source memmove
	// if (from == to || n == 0)
	// 	return dest;
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	// char	b[0xF0];
	// ft_memmove(NULL, b, 5);
	// memmove(NULL, b, 5);

	// char	c[0xF0];
	// ft_memmove(c, NULL, 5);
	// memmove(c, NULL, 5);

		char str1[] = "xxxxxxx";
	int i;

	printf("before:");
	i = 0;
	while (i < 7)
	{
		printf("%d ",str1[i]);
		i++;
	}
	printf("\n");

	ft_memmove(str1, "aa\0aaa", 6);

	printf("after:");
	i = 0;
	while (i < 7)
	{
		printf("%d ",str1[i]);
		i++;
	}
	printf("\n");
	return (0);
}
*/
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char str[] = "1234567890";

	ft_memcpy(str + 3, str, 5); // undefined
	// ft_memmove(str + 3, str, 5); // defined
	printf("%s\n", str);
	return (0);
}
*/
