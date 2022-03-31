#include "lexer_and_parser.h"

t_ms_ast	*lexer_and_parser(char *str)
{
	char		**tokenized_line;
	char		***splited_pipe;
	t_ms_ast	*ms_ast;

	tokenized_line = tokenize_main(str);
	if (!tokenized_line)
	{
		//フリー処理
		return (NULL);
	}
	printf("source_line:[%s]\n", str);
	int i = 0;
	printf("result_line:");
	while (tokenized_line[i])
	{
		printf("[%s]", tokenized_line[i++]);
	}
	printf("\ntooken_count:%d\n", i);

	splited_pipe = split_by_pipe(tokenized_line);
	if (!splited_pipe)
	{
		//フリー処理
		return (NULL);
	}
	return (pipe_branch(splited_pipe));
}

static void print_list(t_list *list)
{
	while (list)
	{
		printf("[%s]", (char *)list->content);
		list = list->next;
	}
	printf("\n");
	return ;
}

static void print_ast(t_ms_ast *ms_ast)
{
	if (ms_ast->left_node)
		print_ast(ms_ast->left_node);
	if (ms_ast->left_node && ms_ast->left_node->cmd_info_list)
		print_list(ms_ast->left_node->cmd_info_list);
	if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
		print_list(ms_ast->right_node->cmd_info_list);
	return ;
}

int	main(void)
{
	// char 		str[] = "<cat file2|grep \"he' ohayo-'llo\"||||wc -l  ><<< > file2 >";
	char		str[] = "ls | cat file2| grep -i \"first\" | wc -l > outfile";
	t_ms_ast	*ms_ast;
	char 		**tokenized_line;

	ms_ast = lexer_and_parser(str);
	printf("\n↓print_ast\n\n");
	print_ast(ms_ast);
	return (0);
}
