/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 16:43:46 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/19 10:22:09 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	j = 0;
	while (dst[j])
		j++;
	i = 0;
	while ((i < (dstsize - dst_len) - 1) && src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dst_len + src_len);
}
// man -> It will append at most dstsize - strlen(dst) - 1 characters.
// Basically, the return value of strlcat is dstlen+srclen.
// However, if dstlen is smaller than dstsize,
// it cannot be connected, so the return value is dstsize+srclen.
// If you compare it with strlen(dst) after the function call,
// you can see if you were able to connect to the end.
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char dest[30];
	memset(dest, 0, 30);
	char dest2[30];
	memset(dest2, 0, 30);

	printf("%zu == %zu\n", strlcat(dest, "123", 3), ft_strlcat(dest2, "123", 3));
	printf("0 == %d\n",strcmp(dest, dest2));
	printf("%s == %s\n",dest, dest2);
	write(1, "\n", 1);
	memset(dest, 0, 30);
	memset(dest2, 0, 30);
	printf("%zu == %zu\n",ft_strlcat(dest, "123", 4), ft_strlcat(dest2, "123", 4));
	printf("%s == %s\n",dest, dest2);
	printf("0 == %d\n",strcmp(dest, dest2));
	return (0);
}
*/
