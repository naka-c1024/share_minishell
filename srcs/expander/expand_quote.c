/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 08:24:08 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/18 13:54:42 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static size_t	count_quote(char *str, int c)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

void	expand_single(char **str)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	quote_cnt;

	quote_cnt = count_quote(*str, '\'');
	ptr = (char *)x_malloc(sizeof(char) * ft_strlen(*str) - quote_cnt + 1);
	i = 0;
	j = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] != '\'')
		{
			ptr[j] = (*str)[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	free(*str);
	*str = ptr;
}

void	expand_double(char **str, t_envlist *envlist)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	quote_cnt;

	quote_cnt = count_quote(*str, '\"');
	ptr = (char *)x_malloc(sizeof(char) * ft_strlen(*str) - quote_cnt + 1);
	i = 0;
	j = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] != '\"')
		{
			ptr[j] = (*str)[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	free(*str);
	*str = ptr;
	expand_dollar(str, envlist);
}
