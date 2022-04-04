/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:30:32 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/04 06:05:55 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_AND_PARSER_H
# define LEXER_AND_PARSER_H

#include "minishell.h"

typedef	struct s_tokenize_info
{
	char	**tokenized_line;
	char	*line;
	int		*line_index;
	int		*line_start_index;
	int		*tl_index;
}	t_tokenize_info;

typedef	struct s_sbp_info
{
	char	**result;
	char	*cmd_line;
	int		*line_index;
	int		*line_start_index;
	int		*tl_index;
}	t_sbp_info;

char		**tokenize_main(char *line);
size_t		tokens_count(char *line);
char		***split_by_pipe(char **cmd_line);
t_ms_ast	*pipe_branch(char ***all_cmd_line);
t_ms_ast	*cmd_branch(char ****all_cmd_line_addr);
t_ms_ast	*new_cmd_node(char ****all_cmd_line_addr);
t_ms_ast	*new_pipe_node(t_ms_ast *left, t_ms_ast *right);

#endif
