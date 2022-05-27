/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:25:28 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/18 10:46:18 by kahirose         ###   ########.fr       */
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
	if (t_info->line[*(t_info->line_index)] != target)
	{
		error_occuration_at_tokenize(&t_info, true);
		return (false);
	}
	(*(t_info->line_index))++;
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, *(t_info->line_start_index), \
			*(t_info->line_index) - *(t_info->line_start_index));
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
	{
		error_occuration_at_tokenize(&t_info, false);
		return (false);
	}
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
		error_occuration_at_tokenize(&t_info, true);
		return (false);
	}
	last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '<') //リダイレクトでも'>'こっち向きは実行できるっぽい
	{
		error_occuration_at_tokenize(&t_info, true);
		return (false);
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, (*(t_info->line_index))++, 1);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
	{
		error_occuration_at_tokenize(&t_info, false);
		return (false);
	}
	*(t_info->line_start_index) = *(t_info->line_index);
	return (true);
}

bool	single_redirect_separator(t_tokenize_info *t_info)
{
	char	last_token;

	if (!take_pre_string(t_info))
		return (false);
	if (*(t_info->tl_index) != 0)
	{
		last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
		{
			error_occuration_at_tokenize(&t_info, true);
			return (false);
		}
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, (*(t_info->line_index))++, 1);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
	{
		error_occuration_at_tokenize(&t_info, false);
		return (false);
	}
	*(t_info->line_start_index) = *(t_info->line_index);
	return (true);
}

bool	double_redirect_separator(t_tokenize_info *t_info)
{
	char	last_token;

	if (!take_pre_string(t_info))
		return (false);
	if (*(t_info->tl_index) != 0)
	{
		last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
		{
			error_occuration_at_tokenize(&t_info, true);
			return (false);
		}
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, *(t_info->line_index), 2);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
	{
		error_occuration_at_tokenize(&t_info, false);
		return (false);
	}
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
