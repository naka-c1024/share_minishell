/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:05:35 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/19 17:20:55 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if (c)
	{
		while (i--)
			if (s[i] == (char)c)
				return ((char *)&s[i]);
		return (NULL);
	}
	return ((char *)&s[i]);
}
// Note the decrement in the size_t type.(over flow)
/*
#include <libc.h>
int	main(void)
{
	// int -> segmentation fault
	char	*s = calloc((size_t)INT_MAX + 200, sizeof(char));
	ft_memset(s, 'a', (size_t)INT_MAX + 199);
	// s[(size_t)INT_MAX + 190] = 'A'; // back
	s[0] = 'A'; // front
	printf("%p = %p\n", strrchr(s, 'A'), ft_strrchr(s, 'A'));
	free(s);

	char	*str = "tripouille";
	printf("%p = %p\n", strrchr(str, '\0'), ft_strrchr(str, '\0'));
	printf("%s = %s\n", strrchr(str, 'A'), ft_strrchr(str, 'A'));
	printf("%s = %s\n", strrchr(str, 'i'), ft_strrchr(str, 'i'));
	printf("%s = %s\n", strrchr(str, 't'), ft_strrchr(str, 't'));
	printf("%s = %s\n",
		strrchr(str, 't' + 256), ft_strrchr(str, 't' + 256));
	printf("%s = %s\n",
		strrchr(str, 't' + 512), ft_strrchr(str, 't' + 1024));
	return (0);
}
 */
/*
// The execution speed is the same
// whether you search from the front or from the back.
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			ptr = (char *)&s[i];
		i++;
	}
	return (ptr);
}
 */
