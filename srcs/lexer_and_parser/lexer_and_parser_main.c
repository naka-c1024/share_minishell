/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:30 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/24 11:10:04 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

t_ms_ast	*lexer_and_parser(char *str, size_t *process_cnt)
{
	char		**tokenized_line;
	char		***splited_pipe;
	t_ms_ast	*ms_ast;

	tokenized_line = tokenize_main(str);
	if (!tokenized_line)
		;
	// print_tokenized_line(tokenized_line);
	splited_pipe = split_by_pipe(tokenized_line, process_cnt);
	if (!splited_pipe)
		;
	// print_sbp(splited_pipe);
	ms_ast = make_ast(splited_pipe);
	if (!ms_ast)
		;
	// printf("\n↓print_ast\n\n");
	// print_ast(ms_ast);
	return (ms_ast);
}


// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q lexer_and_parser");
// }

// int	main(void)
// {
// 	// char 		str[] = "<cat file2|grep \"he' ohayo-'llo\"||||wc -l  ><<< > file2 >";
// 	// char		str[] = ">>ls |<<| cat file2 >> file3|| grep -i  \"first\" | wc -l >> outfile";
// 	// char		str[] = "cat file file2 file3  | grep aius\"fir'hello'\"st | wc    | ss >>";
// 	char		str[] = "export TEST=\"hello\"";
// 	// char 		str[] = "";
// 	char 		**tokenized_line;
// 	t_ms_ast	*ms_ast;
// 	size_t		tl_len;

// 	printf("source_line:[%s]\n", str);
// 	ms_ast = lexer_and_parser(str);
// 	if (!ms_ast)
// 		return (0);
// 	// system("leaks -q lexer_and_parser");
// 	free_ast(ms_ast);
// 	// system("leaks -q lexer_and_parser");
// 	return (0);
// }

//パイプが最初or最後にあればsyntax_error
//クォーとが偶数子でなかった場合
//パイプが二つ続く場合
//リダイレクト関係
// < |
