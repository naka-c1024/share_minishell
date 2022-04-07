/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:28:42 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/07 10:29:50 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

void	error_occuration_at_make_ast(t_make_ast_info *ma_info, \
								t_ms_ast *right, bool is_error)
{
	if (right)
		free_node(right);
	if (is_error)
	{
		if (ma_info->all_cmd_line)
			free_3d_line(ma_info->all_cmd_line);
		if (ma_info->ms_ast && ma_info->ms_ast->type == PIPE)
			free_ast(ma_info->ms_ast);
		if (ma_info->ms_ast)
			free_node(ma_info->ms_ast);
		free(ma_info);
		printf("error\n");
		exit(1);
	}
	free_3d_line(ma_info->all_cmd_line);
	free(ma_info);
}
//51行目：最後のみfree_astではfreeされないという想定かつ、
//初っ端COMMANDノード(つまりシングルプロセスのコマンドライン）だった場合は逆にこれのみで良いという想定

//46行目：//これはcmd_info_lineから直接参照されているようになったのでfreeしてはいけない　
// （cmd_info_lineは新しく文字列をマロックしておらすポインタの代入のみであるということ）
