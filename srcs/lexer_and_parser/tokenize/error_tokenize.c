/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:10:11 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 02:12:11 by kahirose         ###   ########.fr       */
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
}

void	error_occuration_at_tokenize(t_tokenize_info **t_info, char *target)
{
	if (t_info && *t_info)
		free_tokenize_info(t_info);
	printf("minishell: syntax error near unexpected token `%s'\n", target);
}
//t_info->lineはmainでのちにフリーする
