/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 01:09:22 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 03:36:34 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

bool	is_valid_pre_string(int line_index, char target)
{
	if (line_index == 0 || target == '|' || target == ' ' || \
		target == '"' || target == '\'' || target == '>' || target == '<')
		return (false);
	return (true);
}

static int	last_section(t_tokenize_info *t_info)
{
	int		i;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	return (i);
}

size_t	tokens_count(t_tokenize_info *t_info)
{
	size_t	tl_count;

	tl_count = 0;
	while (t_info->line[*(t_info->line_index)])
	{
		if (t_info->line[*(t_info->line_index)] == ' ')
			tl_count += space_section(t_info);
		else if (t_info->line[*(t_info->line_index)] == '|')
			tl_count += pipe_section(t_info);
		else if (is_quote(t_info))
			tl_count += quote_section(t_info);
		else if (is_double_redirect(t_info))
			tl_count += double_redirect_section(t_info);
		else if (is_single_redirect(t_info))
			tl_count += single_redirect_section(t_info);
		else
			(*(t_info->line_index))++;
	}
	tl_count += last_section(t_info);
	*(t_info->line_index) = 0;
	return (tl_count);
}
