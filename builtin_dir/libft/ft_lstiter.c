/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:42:43 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/22 14:24:22 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
void	function(void *argument)
{
	printf("%s\n", (char *)argument);
}

int	main(void)
{
	t_list	*a;
	t_list	*b;
	t_list	*c;

	a = ft_lstnew("first");
	b = ft_lstnew("second");
	c = ft_lstnew("third");

	ft_lstadd_back(&a, b);
	ft_lstadd_back(&a, c);
	ft_lstiter(a, function);
	return (0);
}
*/
