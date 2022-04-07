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
