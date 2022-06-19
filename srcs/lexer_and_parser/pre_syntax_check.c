/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_syntax_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:20:49 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/19 15:35:42 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

bool	last_pipe_check(char *line)
{
	size_t	idx;
	size_t	position;

	idx = 0;
	position = 0;
	while (line[idx])
	{
		if (line[idx] == '|')
			position = idx;
		idx++;
	}
	if (position != 0)
	{
		position++;
		while (line[position] && line[position] == ' ')
			position++;
		if (line[position] == '\0')
			return (false);
	}
	return (true);
}

bool	quote_integrity_check(char *line)
{
	char	target_quote;
	size_t	idx;

	idx = 0;
	target_quote = '\0';
	while (line[idx])
	{
		if (line[idx] == '\'' || line[idx] == '"')
		{
			if (!target_quote)
				target_quote = line[idx];
			else if (line[idx] == target_quote)
				target_quote = '\0';
		}
		idx++;
	}
	if (target_quote)
		return (false);
	return (true);
}

int	is_syntax_status(char *line)
{
	if (!quote_integrity_check(line))
		return (QUOTE);
	if (!last_pipe_check(line))
		return (PIPE);
	return (CORRECT);
}

char	*inserted_eof(char *line, bool *right_syntax)
{
	*right_syntax = false;
	write(STDERR_FILENO, "my_shell: syntax error: unexpected end of file\n", 48);
	g_exit_status = 258;
	return (line);
}

char	*pre_syntax_check(char *line, bool *right_syntax)
{
	char	*result;
	char	*temp;
	char	*nl_temp;
	int		state;

	state = is_syntax_status(line);
	while (state)
	{
		if (state == QUOTE)
		{
			nl_temp = ft_x_strjoin(line, "\n");
			free(line);
			line = nl_temp;
		}
		temp = readline(">");
		if (!temp)
			return (inserted_eof(line, right_syntax));
		result = ft_x_strjoin(line, temp);
		state = is_syntax_status(result);
		free(temp);
		free(line);
		line = result;
	}
	return (line);
}
