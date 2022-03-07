/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:56:01 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/30 15:35:17 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_list;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		new_list = ft_lstnew((*f)(lst->content));
		if (!new_list)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, new_list);
		lst = lst->next;
	}
	return (head);
}

/*
#include <libc.h>
void	del(void *tmp)
{
	free(tmp);
}
// 小文字を大文字に変えるだけの関数
void	*f(void	*ptr)
{
	size_t	i = 0;
	char	*str = ptr;

	if (!ptr)
		return (NULL);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return ((void *)str);
}

int main(int argc, char const *argv[])
{
	t_list	*a;
	t_list	*b;
	t_list	*c;
	t_list	*ret;

	if (argc != 4)
	{
		printf("!?!?!?Bad number of arguments!?!?!?\n");
		return (0);
	}
	a = ft_lstnew(ft_strdup(argv[1]));
	b = ft_lstnew(ft_strdup(argv[2]));
	c = ft_lstnew(ft_strdup(argv[3]));
	ft_lstadd_back(&a, b);
	ft_lstadd_back(&a, c);
	printf("before\n");
	printf("%s\n", (char *)a->content);
	printf("%s\n", (char *)a->next->content);
	printf("%s\n", (char *)a->next->next->content);

	ret = ft_lstmap(a, f, del);

	printf("---------------------\nafter\n");
	printf("%s\n", (char *)ret->content);
	printf("%s\n", (char *)ret->next->content);
	printf("%s\n", (char *)ret->next->next->content);
	return 0;
}
 */
