/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_section.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 01:57:12 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 02:02:11 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

int	space_section(t_tokenize_info *t_info)
{
	int	i;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	while (t_info->line[*(t_info->line_index)] == ' ')
		(*(t_info->line_index))++;
	return (i);
}

int	pipe_section(t_tokenize_info *t_info)
{
	int		i;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	i++;
	(*(t_info->line_index))++;
	return (i);
}

int	quote_section(t_tokenize_info *t_info)
{
	char	target;

	target = t_info->line[*(t_info->line_index)];
	(*(t_info->line_index))++;
	while (t_info->line[*(t_info->line_index)] && \
			t_info->line[*(t_info->line_index)] != target)
		(*(t_info->line_index))++;
	(*(t_info->line_index))++;
	return (1);
}

int	single_redirect_section(t_tokenize_info *t_info)
{
	int	i;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	(*(t_info->line_index))++;
	i++;
	return (i);
}

int	double_redirect_section(t_tokenize_info *t_info)
{
	int		i;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	*(t_info->line_index) += 2;
	i++;
	return (i);
}
