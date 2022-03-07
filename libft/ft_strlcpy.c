/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 16:03:20 by ynakashi          #+#    #+#             */
/*   Updated: 2021/08/28 16:17:39 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	buff[100];
	char	buff2[100];

	printf("%lu = %lu\n",
		ft_strlcpy(buff, "abcdefg", 4),strlcpy(buff2, "abcdefg", 4));
	printf("%s = %s\n", buff, buff2);

	memset(buff,0,100);
	memset(buff2,0,100);
	printf("%lu = %lu\n",
		ft_strlcpy(buff, "abcdefghijkl", 10),strlcpy(buff2, "abcdefghijkl", 10));
	printf("%s = %s\n", buff, buff2);
	return (0);
}
*/
