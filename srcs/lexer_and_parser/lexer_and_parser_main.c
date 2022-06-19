/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:30 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/19 15:37:56 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

t_ms_ast	*lexer_and_parser(char **line, size_t *process_cnt)
{
	char		**tokenized_line;
	char		***splited_pipe;
	t_ms_ast	*ms_ast;
	bool		right_syntax;

	right_syntax = true;
	init_signal(SIGINT, sigint_after_rl_in_command_read);
	*line = pre_syntax_check(*line, &right_syntax);
	if (!right_syntax)
		return (NULL);
	tokenized_line = tokenize_main(*line);
	if (!tokenized_line)
	{
		g_exit_status = 258;
		return (NULL);
	}
	splited_pipe = split_by_pipe(tokenized_line, process_cnt);
	ms_ast = make_ast(splited_pipe);
	init_signal(SIGINT, sigint_before_rl);
	return (ms_ast);
}
