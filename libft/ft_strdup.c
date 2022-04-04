/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:32:46 by ynakashi          #+#    #+#             */
/*   Updated: 2022/04/04 06:56:30 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	ptr = (char *)malloc(s1_len + 1);
	if (!ptr)
		return (NULL);
	else
		ft_strlcpy(ptr, s1, s1_len + 1);
	return (ptr);
}
// You don't need to set errno explicitly because malloc will set it.
//not NULL guard
/*
#include <libc.h>
int main (void)
{
	// ft_strdup(NULL);
	// strdup(NULL);

	char *p;
	char *q;
	char str[] = "abcd\0e";

	p = ft_strdup(str);
	q = strdup(str);
	str[0] = 'z';

	printf("before : %s\n",str);
	printf("%s = %s\n", p, q);
	free(p);
	free(q);
	return (0);
}
 */
