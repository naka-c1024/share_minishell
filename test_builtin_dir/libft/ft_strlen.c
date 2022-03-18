/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 15:51:22 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/17 21:52:20 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (*str++ != '\0')
		length++;
	return (length);
}
// str == NULL -> segmentation fault
/*
#include<stdio.h>
#include <string.h>
int	main(void)
{
	printf("%zu\n", ft_strlen("Tokyo"));
	printf("%zu\n", ft_strlen(""));
	printf("%zu\n", ft_strlen("\0abc"));
	printf("%zu\n", ft_strlen(NULL));
	return (0);
}
*/
