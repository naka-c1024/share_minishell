/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:27:34 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/22 11:22:25 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
// subject -> Finally, the pointer to the list must be set to NULL.
// * lst == NULLとlst == NULLの違い
// lstがNULLの場合、リスト自体が存在しないという意味である。
// * lstはlstの最初のアドレス、headを意味するので、リスト内にノードが存在しないという意味である。
// 今回は後者
// gcc -g -fsanitize=address ft_lstclear.c libft.a && ./a.out abc def
/*
#include <stdio.h>
void	del(void *tmp)
{
	write(STDOUT_FILENO, "o", 1);
	free(tmp);
	write(STDOUT_FILENO, "k\n", 2);
}
// leaks -quiet -atExit --
int main(int argc, char const *argv[])
{
	t_list *a;
	t_list *b;

	if (argc != 3)
	{
		printf("!?!?!?Bad number of arguments!?!?!?\n");
		return (0);
	}
	a = ft_lstnew(ft_strdup(argv[1]));
	b = ft_lstnew(ft_strdup(argv[2]));
	ft_lstadd_back(&a, b);
	printf("%s\n", (char *)a->content);
	printf("%s\n", (char *)a->next->content);
	ft_lstclear(&a, del);
	printf("%p\n", a);
	printf("%p\n", &a);
	return 0;
}
 */
