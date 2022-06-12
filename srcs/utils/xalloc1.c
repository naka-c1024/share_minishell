/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 03:37:49 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 04:09:24 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*x_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("minishell");
		exit(1);
	}
	return (ptr);
}

void	*ft_x_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		perror("minishell");
		exit(1);
	}
	return (ptr);
}

t_list	*ft_x_lstnew(void *content)
{
	t_list	*new_element;

	new_element = ft_lstnew(content);
	if (!new_element)
	{
		perror("minishell");
		exit(1);
	}
	return (new_element);
}
//ft_calloc
//ft_split
//ft_strjoin
//ft_lst系
//int	main(void)
//{
	//char	*str1 = "aaebbelle";
	//char	**result;

	//result = ft_x_split(str1, 'e');
	//printf("%s\n", result[2]);
	//return (0);
//}
