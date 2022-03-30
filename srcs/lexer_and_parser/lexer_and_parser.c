#include "lexer_and_parser.h"

t_ms_ast	*lexer_and_parser(char *str)
{
	char		**tokenized_line;
	char		***splited_pipe;
	t_ms_ast	*ms_ast;

	tokenized_line = tokenize_main(str);

	int i = 0;
	while (tokenized_line[i])
	{
		printf("[%s]\n", tokenized_line[i++]);
	}
	if (!tokenized_line)
	{
		//フリー処理
		return (NULL);
	}
	splited_pipe = split_by_pipe(tokenized_line);
	if (!splited_pipe)
	{
		//フリー処理
		return (NULL);
	}
	return (pipe_branch(splited_pipe));
}

int	main(void)
{
	char 		str[] = "cat file2|grep \"hello\"||||wc -l  > file2";//スペースの後ろにセパレータが来るとまずい
	t_ms_ast	*ms_ast;
	char 		**tokenized_line;

	printf("%s\n", str);
	tokenized_line = tokenize_main(str);

	int i = 0;
	while (tokenized_line[i])
	{
		printf("[%s]\n", tokenized_line[i++]);
	}
	// ms_ast = lexer_and_parser(str);
	return (0);
}
