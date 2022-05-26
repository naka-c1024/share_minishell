/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:30:32 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/22 10:40:13 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_AND_PARSER_H
# define LEXER_AND_PARSER_H

# include "minishell.h"

typedef struct s_tokenize_info
{
	char	**tokenized_line;
	char	*line;
	int		*line_index;
	int		*line_start_index;
	int		*tl_index;
}	t_tokenize_info;

typedef struct s_make_ast_info
{
	t_ms_ast	*ms_ast;
	char		***all_cmd_line;
	int			*fir;
	int			*sec;
}	t_make_ast_info;

//debug用==============================================
void	print_ast(t_ms_ast *ms_ast);
void	print_sbp(char ***sbp);
void	print_tokenized_line(char **tokenized_line);
//debug用===============================================

char		**tokenize_main(char *line);
void		*error_occuration_at_tokenize(t_tokenize_info **t_info, bool is_syntax);
size_t		tokens_count(t_tokenize_info *t_info);
char		***split_by_pipe(char **cmd_line, size_t *process_cnt);
void		free_2d_line(char **two_d_line);
void		free_3d_line(char ***three_d_line);
t_ms_ast	*make_ast(char ***all_cmd_line);
void		make_ast_exe(t_make_ast_info **ma_info, char ***all_cmd_line);
void		error_occuration_at_make_ast(t_make_ast_info *ma_info, t_ms_ast *right, bool is_error);

//token_checker==========
bool	is_double_redirect(t_tokenize_info *t_info);
bool	is_single_redirect(t_tokenize_info *t_info);
bool	is_quote(t_tokenize_info *t_info);

//separator==============
bool	space_separator(t_tokenize_info *t_info);
bool	double_redirect_separator(t_tokenize_info *t_info);
bool	single_redirect_separator(t_tokenize_info *t_info);
bool	pipe_separator(t_tokenize_info *t_info);
bool	quote_separator(t_tokenize_info *t_info);
bool	take_pre_string(t_tokenize_info *t_info);


#endif
