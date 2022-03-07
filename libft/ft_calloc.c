/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:31:56 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/21 17:08:15 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	if (!count || !size)
	{
		count = 1;
		size = 1;
	}
	errno = 0;
	if (count > SIZE_MAX / size)
	{
		errno = ENOMEM;
		return (NULL);
	}
	tmp = malloc(count * size);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, (count * size));
	return (tmp);
}
// You don't need to set errno explicitly because malloc will set it.
// man : count or size == 0 -> NULL or ptr
// guacamole -> ptr
// #include <libc.h>
// int main(void)
// {
// 	char	*str = calloc(0,sizeof(char));
// 	// printf("%s\n", str);
// 	// printf("%s\n", NULL);
// 	// printf("%p\n", str);
// 	return (0);
// }
// calloc has overflow protection.
// #include <libc.h>
// #include <malloc/malloc.h>
// int	main(void)
// {
// 	char	*ptr = calloc(SIZE_MAX - 100, 3);
// 	// char	*ptr = calloc(100, 3);
// 	printf("%zu\n", malloc_size(ptr));
// 	free(ptr);
// }
/*
#include <libc.h>
int	main(void)
{
	// printf("%s\n",ft_calloc(2, SIZE_MAX));
	// printf("%s\n",strerror(errno));

	printf("%s : %s\n",(char *)ft_calloc(42, 2), (char *)calloc(42, 2));
	printf("%s : %s\n",(char *)ft_calloc(2, SIZE_MAX), (char *)calloc(2, SIZE_MAX));
	printf("%s : %s\n",(char *)ft_calloc(SIZE_MAX, 2),(char *)calloc(SIZE_MAX, 2));
	printf("%s : %s\n",(char *)ft_calloc(0, 0), (char *)calloc(0, 0));
	printf("%s : %s\n",(char *)ft_calloc(0, 1), (char *)calloc(0, 1));
	printf("%s : %s\n",(char *)ft_calloc(1, 0), (char *)calloc(1, 0));
	return (0);
}
*/
