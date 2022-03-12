/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 22:38:46 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/26 10:34:44 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
// パラメータとして要素を受け取り、パラメータとして与えられた関数'del'を使用して
// 要素の内容のメモリを解放し、要素を解放します。
// next'のメモリは解放してはならない。
/*
#include <stdio.h>
void	del(void *tmp)
{
	write(STDOUT_FILENO, "o", 1);
	free(tmp);
	write(STDOUT_FILENO, "k\n", 2);
}

// 変数として覚えていたらleakにはならない?->system関数では検証不可
// leaks -quiet -atExit --を使う
int	main(int argc, char const *argv[])
{
	t_list	*a;

	if (argc != 2)
	{
		printf("Bad number of arguments.\n");
		return (0);
	}
	a = ft_lstnew((void *)ft_strdup(argv[1]));
	printf("%s\n", (char *)a->content);
	ft_lstdelone(a, del);
	// ft_lstdelone(a, NULL);
	return 0;
}
 */
