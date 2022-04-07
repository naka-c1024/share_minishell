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
}

static void crawl_ast(t_ms_ast *ms_ast)
{
    if (ms_ast->left_node && ms_ast->type == PIPE)
        crawl_ast(ms_ast->left_node);
    if (ms_ast->left_node && ms_ast->left_node->cmd_info_list)
        print_list(ms_ast->left_node->cmd_info_list);
    if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
        print_list(ms_ast->right_node->cmd_info_list);
}

void print_ast(t_ms_ast *ms_ast)
{
	if (ms_ast && ms_ast->type == PIPE)
		crawl_ast(ms_ast);
	else if (ms_ast && ms_ast->type == COMMAND)
		print_list(ms_ast->cmd_info_list);
}

void	print_sbp(char ***sbp)
{
	int fir = 0;
	int sec;
	printf("\n↓splited_by_pipe\n\n");
	while (sbp[fir])
	{
		sec = 0;
		while (sbp[fir][sec])
			printf("[%s]", sbp[fir][sec++]);
		printf("\n");
		fir++;
	}
}

void	print_tokenized_line(char **tokenized_line)
{

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
	printf("\n");
}
