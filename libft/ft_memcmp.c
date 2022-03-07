/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 08:40:59 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/19 19:59:21 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
// man -> treated as unsigned char values,
// so that `\200' is greater than `\0', for example
// not NULL guard
/*
#include <libc.h>
int	main(void)
{
	printf("%d\n",memcmp("abc\0defgh\0ijk","abc\0defgh\0ijz",11));
	printf("%d\n",ft_memcmp("abc\0defgh\0ijk","abc\0defgh\0ijz",11));

	printf("%d\n",memcmp("1234","12345",7));
	printf("%d\n",ft_memcmp("1234","12345",7));

	printf("%d\n",memcmp("123\200","123\0",7));
	printf("%d\n",ft_memcmp("123\200","123\0",7));

	printf("%d\n",memcmp("\0abc\0de","\0abc\0de",7));
	printf("%d\n",ft_memcmp("\0abc\0de","\0abc\0de",7));

	printf("%d\n",memcmp("\0abc\0de","\0abcdef",7));
	printf("%d\n",ft_memcmp("\0abc\0de","\0abcdef",7));
	return (0);
}
 */
