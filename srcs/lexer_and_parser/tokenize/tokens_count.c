/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 01:09:22 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/06 15:44:12 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

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

static bool	is_valid_pre_string(int line_index, char target)
{
	if (line_index == 0 || target == '|' || target == ' ' || \
		target == '"' || target == '\'' || target == '>' || target == '<')
		return (false);
	return (true);
}

static int	last_section(t_tokenize_info *t_info)
{
	char	last_token;
	int		i;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	return (i);
}

static int	space_section(t_tokenize_info *t_info)
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

static int	pipe_section(t_tokenize_info *t_info)
{
	int		i;
	char	last_token;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	i++;
	(*(t_info->line_index))++;
	return (i);
}

static int	quote_section(t_tokenize_info *t_info)
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
	return (1);
}

static int	single_redirect_section(t_tokenize_info *t_info)
{
	int i;
	char	last_token;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	(*(t_info->line_index))++;
	i++;
	return (i);
}

static	int	double_redirect_section(t_tokenize_info *t_info)
{
	int		i;
	char	last_token;

	i = 0;
	if (is_valid_pre_string(*(t_info->line_index), \
		t_info->line[(*(t_info->line_index)) - 1]))
		i++;
	*(t_info->line_index) += 2;
	i++;
	return (i);
}

size_t  tokens_count(t_tokenize_info *t_info)
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
	printf("tl_count:%zu\n", tl_count);
	return (tl_count);
}

// static size_t	tokenize_mains(char *line)
// {
// 	t_tokenize_info	*t_info;
// 	int				line_index;
// 	int				line_start_index;
// 	int				tl_index;

// 	line_index = 0;
// 	line_start_index = 0;
// 	tl_index = 0;
// 	t_info = (t_tokenize_info *)malloc(sizeof(t_tokenize_info));
// 	if (!t_info)
// 		error_occuration_at_tokenize(NULL, false);
// 	t_info->line = line;
// 	t_info->line_index = &line_index;
// 	t_info->line_start_index = &line_start_index;
// 	return (tokens_counts(t_info));
// }

// int main(void)
// {
//     char str[] = "cat 'aiu' file2 ><| > grep >\"he'l'  lo\" | wc -l >> outfile";
//     int  tl_len = 0;

// 	printf("%zu\n", tokenize_mains(str));
//     return (0);
// }
