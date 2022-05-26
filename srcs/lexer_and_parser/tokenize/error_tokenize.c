/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:10:11 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/20 19:35:58 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

static void	free_tokenize_info(t_tokenize_info **t_info)
{
	int	index;

	index = 0;
	if ((*t_info)->tokenized_line)
	{
		while ((*t_info)->tokenized_line[index])
			free((*t_info)->tokenized_line[index++]);
		free((*t_info)->tokenized_line[index]);
	}
	free((*t_info)->tokenized_line);
	//free(*t_info);
	*t_info = NULL;
}

void	*error_occuration_at_tokenize(t_tokenize_info **t_info, bool is_syntax)
{
	if (t_info && *t_info)
		free_tokenize_info(t_info);
	if (is_syntax)
		printf("syntax_error\n");
	else
		printf("malloc_error\n");
	return (NULL);
}
// free((*t_info)->line);//ここは後ほどmainと繋がってから
