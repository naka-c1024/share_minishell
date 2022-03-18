/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:18:00 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/19 16:49:32 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

// NULL->segmentation fault
// int -> crash
// The case of c='\0' returns the last pointer containing '\0' at the end of s.
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char str[] = "012345";

	printf("%s = %s\n", strchr(str, (int)'3'), ft_strchr(str, (int)'3'));
	printf("%s = %s\n", strchr(str, (int)'A'), ft_strchr(str, (int)'A'));
	printf("%s = %s\n", strchr("", (int)'\n'), ft_strchr("", (int)'\n'));
	printf("%p = %p\n", strchr(str, (int)'\0'), ft_strchr(str, (int)'\0'));
	// printf("%s\n", ft_strchr(NULL, (int)'3'));
	return (0);
}
*/
/*
// int -> crash
#include <stdio.h>
int	main(void)
{
	char	*str = calloc((size_t)INT_MAX + 200, sizeof(char));
	char	*ptr;

	ft_memset(str, 'A', (size_t)INT_MAX + 200);
	str[(size_t)INT_MAX +100] = 'a';
	ptr = ft_strchr(str, (int)'a');
	printf("%p\n", ptr);
	free(str);
	return (0);
}
*/
