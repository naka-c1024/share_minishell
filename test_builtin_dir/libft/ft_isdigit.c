/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 17:32:51 by ynakashi          #+#    #+#             */
/*   Updated: 2021/08/07 12:52:10 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (('0' <= c && c <= '9'));
}
/*
**#include <stdio.h>
**int	main(void)
**{
**	char n = 'a';
**
**	printf("%d\n", ft_isdigit(n));
**	return (0);
**}
 */
