/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 11:32:31 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/19 14:48:13 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
// bzero is MACRO
// #if __has_builtin(__builtin___memset_chk) || defined(__GNUC__)
// #undef bzero
// /* void	bzero(void *s, size_t n) */
// #define bzero(dest, ...)
// 		__builtin___memset_chk (dest, 0, __VA_ARGS__, __darwin_obsz0 (dest))
// #endif
/*
**#include <stdio.h>
**int	main(void)
**{
**	int i = -1;
**	char str[5] = "11111";
**	ft_bzero(str+1, 2);
**	while (++i < 5)
**		printf("%c, ", str[i]);
**	return (0);
**}
*/
