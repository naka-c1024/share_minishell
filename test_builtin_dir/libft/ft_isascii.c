/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 14:31:07 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/17 21:44:07 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (0 <= c && c <= 127);
}
// man ascii -> The decimal set:
/*
#include <stdio.h>
int	main(void)
{
	printf("%d\n",ft_isascii(' '));
	printf("%d\n",ft_isascii(129));
	return (0);
}
*/
