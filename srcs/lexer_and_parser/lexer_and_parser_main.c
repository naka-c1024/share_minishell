/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:30 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 01:49:56 by kahirose         ###   ########.fr       */
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

char	*pre_syntax_check(char *line)
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
		result = ft_x_strjoin(line, temp);
		state = is_syntax_status(result);
		free(temp);
		free(line);
		line = result;
	}
	return (line);
}

t_ms_ast	*lexer_and_parser(char **line, size_t *process_cnt)
{
	char		**tokenized_line;
	char		***splited_pipe;
	t_ms_ast	*ms_ast;

	*line = pre_syntax_check(*line);
	tokenized_line = tokenize_main(*line);
	if (!tokenized_line)
		return (NULL);
	splited_pipe = split_by_pipe(tokenized_line, process_cnt);
	ms_ast = make_ast(splited_pipe);
	return (ms_ast);
}
