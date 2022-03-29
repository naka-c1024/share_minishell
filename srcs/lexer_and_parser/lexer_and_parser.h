/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:30:32 by kahirose          #+#    #+#             */
/*   Updated: 2022/03/28 17:32:19 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_AND_PARSER_H
# define LEXER_AND_PARSER_H

#include "minishell.h"

char		***split_by_pipe(char **cmd_line);
t_ms_ast	*pipe_branch(char ***all_cmd_line);
t_ms_ast	*cmd_branch(char ****all_cmd_line_addr);
t_ms_ast	*new_cmd_node(char ****all_cmd_line_addr);
t_ms_ast	*new_pipe_node(t_ms_ast *left, t_ms_ast *right);

#endif
