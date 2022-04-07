/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 06:11:34 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/06 06:17:39 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

t_ms_ast	*make_ast(char ***all_cmd_line)
{
	t_make_ast_info	*ma_info;
	t_ms_ast		*result_ast;
	int				fir;
	int				sec;

	ma_info = (t_make_ast_info *)malloc(sizeof(t_make_ast_info));
	if (!ma_info)
		error_occuration_at_make_ast(NULL, NULL, true);
	fir = 0;
	sec = 0;
	ma_info->fir = &fir;
	ma_info->sec = &sec;
	ma_info->all_cmd_line = all_cmd_line;
	ma_info->ms_ast = NULL;
	make_ast_exe(&ma_info, all_cmd_line);
	result_ast = ma_info->ms_ast;
	error_occuration_at_make_ast(ma_info, NULL, false);
	return (result_ast);
}
