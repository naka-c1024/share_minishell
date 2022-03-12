/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:32:19 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/21 15:38:02 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}
// first -> second -> third
/*
#include <stdio.h>
int	main()
{
	t_list	*a;
	t_list	*b;
	t_list	*c;
	t_list	*lst;

	a = ft_lstnew("first");
	b = ft_lstnew("second");
	c = ft_lstnew("third");
	lst = a;

	ft_lstadd_front(&c, b);
	ft_lstadd_front(&b, a);
	while (lst != NULL)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
	return (0);
}
 */
