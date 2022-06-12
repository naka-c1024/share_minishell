/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:25:28 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 02:05:49 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

bool	quote_separator(t_tokenize_info *t_info)
{
	char	target;

	target = t_info->line[*(t_info->line_index)];
	(*(t_info->line_index))++;
	while (t_info->line[*(t_info->line_index)] && \
			t_info->line[*(t_info->line_index)] != target)
		(*(t_info->line_index))++;
	(*(t_info->line_index))++;
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_x_substr(t_info->line, *(t_info->line_start_index), \
			*(t_info->line_index) - *(t_info->line_start_index));
	*(t_info->line_start_index) = *(t_info->line_index);
	return (true);
}

bool	pipe_separator(t_tokenize_info *t_info)
{
	char	last_token;

	if (!take_pre_string(t_info))
		return (false);
	if (*(t_info->tl_index) == 0)
	{
		error_occuration_at_tokenize(&t_info, "|\0");
		return (false);
	}
	last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '<')
	{
		error_occuration_at_tokenize(&t_info, "|\0");
		return (false);
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_x_substr(t_info->line, (*(t_info->line_index))++, 1);
	*(t_info->line_start_index) = *(t_info->line_index);
	return (true);
}

bool	single_redirect_separator(t_tokenize_info *t_info)
{
	char	last_token;
	char	current_token[2];

	if (!take_pre_string(t_info))
		return (false);
	if (*(t_info->tl_index) != 0)
	{
		last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
		{
			current_token[0] = t_info->line[*(t_info->line_index)];
			current_token[1] = '\0';
			error_occuration_at_tokenize(&t_info, current_token);
			return (false);
		}
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_x_substr(t_info->line, (*(t_info->line_index))++, 1);
	*(t_info->line_start_index) = *(t_info->line_index);
	return (true);
}

bool	double_redirect_separator(t_tokenize_info *t_info)
{
	char	last_token;
	char	current_token[3];

	if (!take_pre_string(t_info))
		return (false);
	if (*(t_info->tl_index) != 0)
	{
		last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
		{
			current_token[0] = t_info->line[*(t_info->line_index)];
			current_token[1] = t_info->line[*(t_info->line_index)];
			current_token[2] = '\0';
			error_occuration_at_tokenize(&t_info, current_token);
			return (false);
		}
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_x_substr(t_info->line, *(t_info->line_index), 2);
	*(t_info->line_index) += 2;
	*(t_info->line_start_index) = *(t_info->line_index);
	return (true);
}

bool	space_separator(t_tokenize_info *t_info)
{
	if (!take_pre_string(t_info))
		return (false);
	while (t_info->line[*(t_info->line_index)] == ' ')
		(*(t_info->line_index))++;
	*(t_info->line_start_index) = *(t_info->line_index);
	return (true);
}
