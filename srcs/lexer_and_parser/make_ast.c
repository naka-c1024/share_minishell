#include "lexer_and_parser.h"

static bool	is_pipe(char ****all_cmd_line_addr)
{
	if (!(*all_cmd_line_addr)[0])
		return (false);
	if ((*all_cmd_line_addr)[0][0][0] != '|')
		return (false);
	(*all_cmd_line_addr)++;
	return (true);
}

t_ms_ast	*cmd_branch(char ****all_cmd_line_addr)
{
	return (new_cmd_node(all_cmd_line_addr));
}

t_ms_ast	*pipe_branch(char ***all_cmd_line)
{
	char		***tmp_line;
	t_ms_ast	*ms_ast;

	tmp_line = all_cmd_line;
	ms_ast = cmd_branch(&all_cmd_line);
	while (1)
	{
		if (is_pipe(&all_cmd_line))//今日ここから
		{
			ms_ast = new_pipe_node(ms_ast, cmd_branch((&all_cmd_line)));
		}
		else
		{
			return (ms_ast);
		}
	}
}

// 必要になったらこれ使おう
// while (1)
// {
// 	if (is_pipe(&all_cmd_line))//今日ここから
// 	{
// 		if (all_cmd_line[0])//圧倒的自信の[0]
// 			ms_ast = new_pipe_node(ms_ast, cmd_branch((&all_cmd_line)));
// 		else //最後がパイプで終わる場合の処理だが実際にはsyntax errorではなく開業されて次のコマンド名入力待ちの状態になる
// 		{
// 			printf("この処理入ることないと思われる：ssyntax_error\n");
// 			exit (0);//free処理も
// 		}
// 	}
// 	else
// 	{
// 		return (ms_ast);
// 	}
// }
