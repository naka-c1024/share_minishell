/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:44:58 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/19 23:08:01 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	if (!n)
		return (NULL);
	str = (const unsigned char *)s;
	i = 0;
	while (n-- > 0)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)str + i);
		i++;
	}
	return (NULL);
}
// not NULL guard
// man -> unsigned, but signed works.
/*
#include <libc.h>
int main(void)
{
	char	*str = "abc\0de\200f";
	printf("%p = %p\n",memchr(str, 'e', 42), ft_memchr(str, 'e', 42));
	printf("%p = %p\n",memchr(str, '\0', 42), ft_memchr(str, '\0', 42));
	printf("%p = %p\n",memchr(str, 'X', 42), ft_memchr(str, 'X', 42));
	printf("%p = %p\n",memchr(str, 'a', 0), ft_memchr(str, 'a', 0));
	printf("%p = %p\n",memchr(str, 'a', 1), ft_memchr(str, 'a', 1));
	printf("%p = %p\n",memchr(str, '\200', 42), ft_memchr(str, '\200', 42));
	return (0);
}
 */
