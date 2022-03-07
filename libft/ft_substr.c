/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:51:49 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/20 20:00:01 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	new_str_len;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start || len == 0)
		return (ft_strdup(""));
	new_str_len = ft_strlen(s + start);
	if (new_str_len < len)
		len = new_str_len;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
// why 22,23 line -> libftTester,libft-unit-test,Libfttest
// If start >= ft_strlen(s), returns an empty string.
// If len == 0, also returns an empty string.
// However, there is no such description in the subject.
/*
#include <stdio.h>
int main(void)
{
	char* str1 = ft_substr("Hello, 42world!", 7, 2);
	printf("42 = %s\n", str1);
	free(str1);
	char* str2 = ft_substr("Hello, 42world!", 20, 2);
	printf(" "" = %s\n", str2);
	free(str2);
	char* str3 = ft_substr("Hello, 42world!", 7, 0);
	printf(" "" = %s\n", str3);
	free(str3);
	char* str4 = ft_substr("Hello, 42world!", 7, 20);
	printf("42world! = %s\n", str4);
	free(str4);
	char* str5 = ft_substr(NULL, 7, 20);
	printf("(null) = %s\n", str5);
	free(str5);
	char* str6 = ft_substr("Hello, 42world!", 0, 20);
	printf("Hello, 42world! = %s\n", str6);
	free(str6);
	return 0;
}
 */
