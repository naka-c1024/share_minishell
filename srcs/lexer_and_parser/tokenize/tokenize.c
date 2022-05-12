/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:17:07 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/24 11:56:55 by kahirose         ###   ########.fr       */
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

static void	take_pre_string(t_tokenize_info *t_info)
{
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
	{
		t_info->tokenized_line[(*(t_info->tl_index))++] = \
			ft_substr(t_info->line, *(t_info->line_start_index), \
				*(t_info->line_index) - *(t_info->line_start_index));
		if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
			error_occuration_at_tokenize(&t_info, false);
	}
}

static void	take_last_string(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	t_info->tokenized_line[*(t_info->tl_index)] = NULL;
	last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '>' || last_token == '<')
		error_occuration_at_tokenize(&t_info, true);
	// free(line);//free_lexer_infoと同じくここも後ほど
	// free(t_info);
}

static void	quote_separator(t_tokenize_info *t_info)
{
	char	target;

	target = t_info->line[*(t_info->line_index)];
	(*(t_info->line_index))++;
	while (t_info->line[*(t_info->line_index)] && \
			t_info->line[*(t_info->line_index)] != target)
		(*(t_info->line_index))++;
	if (t_info->line[*(t_info->line_index)] != target)
		error_occuration_at_tokenize(&t_info, true);
	(*(t_info->line_index))++;
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, *(t_info->line_start_index), \
			*(t_info->line_index) - *(t_info->line_start_index));
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&t_info, false);
	*(t_info->line_start_index) = *(t_info->line_index);
}

static void	pipe_separator(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	if (*(t_info->tl_index) == 0)
		error_occuration_at_tokenize(&t_info, true);
	last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
	if (last_token == '|' || last_token == '<') //リダイレクトでも'>'こっち向きは実行できるっぽい
		error_occuration_at_tokenize(&t_info, true);
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, (*(t_info->line_index))++, 1);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&t_info, false);
	*(t_info->line_start_index) = *(t_info->line_index);
}

static void	single_redirect_separator(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	if (*(t_info->tl_index) != 0)
	{
		last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
			error_occuration_at_tokenize(&t_info, true);
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, (*(t_info->line_index))++, 1);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&t_info, false);
	*(t_info->line_start_index) = *(t_info->line_index);
}

static	void	double_redirect_separator(t_tokenize_info *t_info)
{
	char	last_token;

	take_pre_string(t_info);
	if (*(t_info->tl_index) != 0)
	{
		last_token = t_info->tokenized_line[(*(t_info->tl_index)) - 1][0];
		if (last_token == '>' || last_token == '<')
			error_occuration_at_tokenize(&t_info, true);
	}
	t_info->tokenized_line[(*(t_info->tl_index))++] = \
		ft_substr(t_info->line, *(t_info->line_index), 2);
	if (!(t_info->tokenized_line[(*(t_info->tl_index)) - 1]))
		error_occuration_at_tokenize(&t_info, false);
	*(t_info->line_index) += 2;
	*(t_info->line_start_index) = *(t_info->line_index);
}

static void	space_separator(t_tokenize_info *t_info)
{
	take_pre_string(t_info);
	while (t_info->line[*(t_info->line_index)] == ' ')
		(*(t_info->line_index))++;
	*(t_info->line_start_index) = *(t_info->line_index);
}

static bool	is_quote(t_tokenize_info *t_info)
{
	if (t_info->line[*(t_info->line_index)] == '\'' || \
		t_info->line[*(t_info->line_index)] == '"')
		return (true);
	return (false);
}

static bool	is_single_redirect(t_tokenize_info *t_info)
{
	if (t_info->line[*(t_info->line_index)] == '>' || \
		t_info->line[*(t_info->line_index)] == '<')
		return (true);
	return (false);
}

static bool	is_double_redirect(t_tokenize_info *t_info)
{
	if (!ft_strncmp(&(t_info->line[*(t_info->line_index)]), ">>", 2) || \
		!ft_strncmp(&(t_info->line[*(t_info->line_index)]), "<<", 2))
		return (true);
	return (false);
}

static char	**tokenize(t_tokenize_info *t_info)
{
	char	**tokenized_line;
	size_t	tl_len;

	tl_len = tokens_count(t_info);
	tokenized_line = (char **)ft_calloc(sizeof(char *), tl_len + 1);
	if (!tokenized_line)
		error_occuration_at_tokenize(&t_info, false);
	t_info->tokenized_line = tokenized_line;
	while (t_info->line[*(t_info->line_index)])
	{
		if (t_info->line[*(t_info->line_index)] == ' ')
			space_separator(t_info);
		else if (t_info->line[*(t_info->line_index)] == '|')
			pipe_separator(t_info);
		else if (is_quote(t_info))
			quote_separator(t_info);
		else if (is_double_redirect(t_info))
			double_redirect_separator(t_info);
		else if (is_single_redirect(t_info))
			single_redirect_separator(t_info);
		else
			(*(t_info->line_index))++;
	}
	take_last_string(t_info);
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
	t_info = (t_tokenize_info *)malloc(sizeof(t_tokenize_info));
	if (!t_info)
		error_occuration_at_tokenize(NULL, false);
	t_info->line = line;
	t_info->line_index = &line_index;
	t_info->line_start_index = &line_start_index;
	t_info->tl_index = &tl_index;
	tokenized_line = tokenize(t_info);
	free(t_info);
	return (tokenized_line);
}
