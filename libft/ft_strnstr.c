/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 12:57:01 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/20 19:11:47 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (len - i < ft_strlen(needle))
			return (NULL);
		if (ft_strncmp(&haystack[i], needle, ft_strlen(needle)) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
// man -> If needle is an empty string, haystack is returned
// not NULL guard
// (len-i) represents the number of remaining search characters,
// and if (len-i) is smaller than needle_len,
// the same string will never be found.
/*
#include <libc.h>
int main(void)
{
	char s1[] = "pen pineapple apple pen!";

	printf("%s = %s\n", strnstr(s1, "pine", 10), ft_strnstr(s1, "pine", 10));
	printf("%s = %s\n", strnstr(s1, "pine", 0), ft_strnstr(s1, "pine", 0));
	printf("%s = %s\n", strnstr(s1, "pine", 5), ft_strnstr(s1, "pine", 5));
	printf("%s = %s\n", strnstr(s1, "pin\0e", 10), ft_strnstr(s1, "pin\0e", 10));
	printf("%s = %s\n", strnstr(s1, "", 10), ft_strnstr(s1, "", 10));
	// printf("%s\n", ft_strnstr(s1, NULL, 10)); // segmentation fault
	// printf("%s\n", ft_strnstr(NULL, "hello", 10)); // segmentation fault
	// printf("%s\n", ft_strnstr(NULL, NULL, 10)); // segmentation fault
	// printf("%s\n", ft_strnstr(NULL, NULL, 10)); // segmentation fault
	return (0);
}
 */
