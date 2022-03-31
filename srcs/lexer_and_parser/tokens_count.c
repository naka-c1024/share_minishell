/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 01:09:22 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/01 02:19:41 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "lexer_and_parser.h"

// static int	space_section(char *line, int *line_index_ptr)
// {
//     int i;

//     i = 0;
// 	if (is_valid_pre_string(line, )) //初っ端からスペースだった場合に、空文字列が作られるのを防ぐ
//         i++;
// 	while (l_info->line[*(l_info->line_index)] == ' ')
// 		(*(l_info->line_index))++;
// 	*(l_info->line_start_index) = *(l_info->line_index);
//     return (i);
// }

// size_t  tokens_count(char *line)
// {
//     size_t  line_index;
//     size_t  tl_count;

//     line_index = 0;
//     tl_count = 0;
//     while (line[line_index])
//     {
//         if (l_info->line[*(l_info->line_index)] == ' ')
// 			tl_count += space_section(line, &line_index);
// 		else if (l_info->line[*(l_info->line_index)] == '|')
// 			pipe_section(l_info);
// 		else if (is_quote(l_info))
// 				quote_section(l_info);
// 		else if (is_double_redirect(l_info))
// 			double_redirect_section(l_info);
// 		else if (is_single_redirect(l_info))
// 			single_redirect_section(l_info);
// 		else
// 			(*(l_info->line_index))++;
//     }
//     return (1);
// }

// int main(void)
// {
//     char str[] = "cat file2 | grep \"hello\" | wc -l >> outfile";
//     int  tl_len = 0;

//     tl_len = tokens_count(str);
//     return (0);
// }