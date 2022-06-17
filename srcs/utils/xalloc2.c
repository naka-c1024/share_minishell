/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xalloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 04:07:12 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/15 07:58:42 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
