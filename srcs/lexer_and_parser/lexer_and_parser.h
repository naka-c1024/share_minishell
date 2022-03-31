/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:30:32 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/01 01:17:29 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_AND_PARSER_H
# define LEXER_AND_PARSER_H

#include "minishell.h"

typedef	struct s_lexer_info
{
	char	**tokenized_line;
	char	*line;
	int		*line_index;
	int		*line_start_index;
	int		*tl_index;
}	t_lexer_info;

char		**tokenize_main(char *line);
size_t		tokens_count(char *line);
char		***split_by_pipe(char **cmd_line);
t_ms_ast	*pipe_branch(char ***all_cmd_line);
t_ms_ast	*cmd_branch(char ****all_cmd_line_addr);
t_ms_ast	*new_cmd_node(char ****all_cmd_line_addr);
t_ms_ast	*new_pipe_node(t_ms_ast *left, t_ms_ast *right);

#endif
