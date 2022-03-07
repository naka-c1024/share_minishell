/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:20:49 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/19 17:25:08 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
// why unsigned -> man
// The comparison is done using unsigned characters,
// so that `\200' is greater than `\0'.
// not NULL guard
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	printf("%d = %d\n", strncmp("1234","1235",3), ft_strncmp("1234","1235",3));
	printf("%d = %d\n", strncmp("1234","1235",42), ft_strncmp("1234","1235",42));
	printf("%d = %d\n", strncmp("12\034","1235",3), ft_strncmp("12\034","1235",3));
	printf("%d = %d\n",
		strncmp("test\200", "test\0", 6), ft_strncmp("test\200", "test\0", 6));
	return (0);
}
*/
