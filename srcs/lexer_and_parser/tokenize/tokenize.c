/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:17:07 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/03 19:33:06:48 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

static bool	is_valid_pre_string(int line_index, char target)
{
	if (line_index == 0 || target == '|' || target == ' ' || \
		target == '"' || target == '\'' || target == '>' || target == '<')
		return (false);
	return (true);
}

static bool	take_last_string(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	t_info->tokenized_line[*(t_info->tl_index)] = NULL;
	last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '>' || last_token == '<')
	{
		error_occuration_at_tokenize(&t_info, "newline\0");
		return (false);
	}
	return (true);
}

bool	take_pre_string(t_tokenize_info *t_info)
{
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
	{
		t_info->tokenized_line[(*(t_info->tl_index))++] = \
			ft_x_substr(t_info->line, *(t_info->line_start_index), \
				*(t_info->line_index) - *(t_info->line_start_index));
	}
	return (true);
}

static char	**tokenize(t_tokenize_info *t_info)
{
	char	**tokenized_line;
	size_t	tl_len;
	bool	is_ok;

	tl_len = tokens_count(t_info);
	tokenized_line = (char **)ft_x_calloc(sizeof(char *), tl_len + 1);
	t_info->tokenized_line = tokenized_line;
	is_ok = true;
	while (t_info->line[*(t_info->line_index)])
	{
		if (t_info->line[*(t_info->line_index)] == ' ')
			is_ok = space_separator(t_info);
		else if (t_info->line[*(t_info->line_index)] == '|')
			is_ok = pipe_separator(t_info);
		else if (is_quote(t_info))
			is_ok = quote_separator(t_info);
		else if (is_double_redirect(t_info))
			is_ok = double_redirect_separator(t_info);
		else if (is_single_redirect(t_info))
			is_ok = single_redirect_separator(t_info);
		else
			(*(t_info->line_index))++;
		if (is_ok == false)
			return (NULL);
	}
	if (!take_last_string(t_info))
		return (NULL);
	return (t_info->tokenized_line);
}

char	**tokenize_main(char *line)
{
	t_tokenize_info	*t_info;
	int				line_index;
	int				line_start_index;
	char			**tokenized_line;
	int				tl_index;

	line_index = 0;
	line_start_index = 0;
	tl_index = 0;
	t_info = (t_tokenize_info *)x_malloc(sizeof(t_tokenize_info));
	t_info->line = line;
	t_info->line_index = &line_index;
	t_info->line_start_index = &line_start_index;
	t_info->tl_index = &tl_index;
	tokenized_line = tokenize(t_info);
	free(t_info);
	return (tokenized_line);
}
