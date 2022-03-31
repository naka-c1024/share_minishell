#include "lexer_and_parser.h"

static void print_list(t_list *list)
{
	while (list)
	{
		if (!((char *)list->content)[0])
			printf("\x1b[35m[null]\x1b[39m");
		else
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

static void	print_sbp(char ***sbp)
{
	int fir = 0;
	int sec;
	while (sbp[fir])
	{
		sec = 0;
		while (sbp[fir][sec])
			printf("[%s]", sbp[fir][sec++]);
		printf("\n");
		fir++;
	}
}

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
	else if (!tokenized_line[0])//開業の場合がここに入るかも？ここから目線だとから文字列入力の場合
	{
		return (NULL);
	}
	int i = 0;
	printf("result_line:");
	while (tokenized_line[i])
	{
		if (!tokenized_line[i][0])
		{
			printf("\x1b[35m[null]\x1b[39m");
			i++;
		}
		else
			printf("[%s]", tokenized_line[i++]);
	}
	printf("\ntoken_count:%d\n", i);

	splited_pipe = split_by_pipe(tokenized_line);
	if (!splited_pipe)
	{
		//フリー処理
		return (NULL);
	}
	print_sbp(splited_pipe);
	printf("running31\n");
	return (pipe_branch(splited_pipe));
}


// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

int	main(void)
{
	// char 		str[] = "<cat file2|grep \"he' ohayo-'llo\"||||wc -l  ><<< > file2 >";
	// char		str[] = ">>ls |<<| cat file2 >> file3|| grep -i  \"first\" | wc -l >> outfile";
	char		str[] = "cat file | grep \"fir'hello'st\" | wc -l";
	// char 		str[] = "";
	char 		**tokenized_line;
	t_ms_ast	*ms_ast;
	size_t		tl_len;

	// tl_len = tokens_count(str);
	printf("source_line:[%s]\n", str);
	ms_ast = lexer_and_parser(str);
	if (!ms_ast)
		return (0);
	printf("\n↓print_ast\n\n");
	print_ast(ms_ast);
	return (0);
}
