/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crawl_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:48:31 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/09 05:35:31 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void crawl_ast(t_ms_ast *ms_ast, )//関数ポインタ使いたいが何型？
// {
//     if (ms_ast->left_node && ms_ast->type == PIPE)
//         crawl_ast(ms_ast->left_node);
//     if (ms_ast->left_node && ms_ast->left_node->cmd_info_list)
//         print_list(ms_ast->left_node->cmd_info_list);
//     if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
//         print_list(ms_ast->right_node->cmd_info_list);
// }
