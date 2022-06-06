/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 03:37:49 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/02 16:57:11 by kahirose         ###   ########.fr       */
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

char	**ft_x_split(const char *s, char c)
{
	char	**result;

	result = ft_split(s, c);
	if (!result)
	{
		perror("minishell");
		exit(1);
	}
	return (result);
}

char	*ft_x_strjoin(const char *s1, const char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
	{
		perror("minishell");
		exit(1);
	}
	return (result);
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

void	*ft_x_strdup(const char *s1)
{
	void	*result;

	result = ft_strdup(s1);
	if (!result)
	{
		perror("minishell");
		exit(1);
	}
	return (result);
}

char	*ft_x_substr(const char *s, unsigned int start, size_t len)
{
	char	*result;

	result = ft_substr(s, start, len);
	if (!result)
	{
		perror("minishell");
		exit(1);
	}
	return (result);
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
