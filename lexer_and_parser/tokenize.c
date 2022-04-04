#include "lexer_and_parser.h"
#include "minishell.h"

static char	**tokenize(char *line)
{
	char	**tokenized_line;
	char	separator[10] = {' ', '|', '\'', '"'};
	int		line_index;
	int		line_start_index;
	int		separator_index;
	int		tl_index;
	int		flag;

	tokenized_line = (char **)malloc(sizeof(char *) * 30); //size_count関数を入れる
	line_index = 0;
	tl_index = 0;
	while (line[line_index] && line[line_index] == ' ')
		line_index++;
	line_start_index = line_index;
	while (line[line_index])
	{
		separator_index = 0;
		flag = 0;
		if (line[line_index] == ' ')
		{
			tokenized_line[tl_index++] = ft_substr(line, line_start_index, line_index - line_start_index);
			printf("space:[%s]\n", tokenized_line[tl_index - 1]);
			while (line[line_index] && line[line_index] == ' ')
				line_index++;
			line_start_index = line_index;
		}
		while (line[line_index] && separator[separator_index] && flag == 0)
		{
			if (line[line_index] == separator[separator_index])
			{
				if (line[line_index] == '\'' || line[line_index] == '"')
				{
					line_index++;
					while (line[line_index] && line[line_index] != separator[separator_index])
						line_index++;
					if (line[line_index] == separator[separator_index])
						line_index++;
					else
					{
						//'\0'終端まで到達し、期待されたquoteが来なかった場合
						//ここで、syntax_error的なものを出したい
						;
					}
					tokenized_line[tl_index++] = ft_substr(line, line_start_index, line_index - line_start_index);
					while (line[line_index] && line[line_index] == ' ')
						line_index++;
					line_start_index = line_index; //なぜここは+1でうまく行くのに93行目ではしなくいいのか
				}
				else if (line_index == line_start_index)//直前がスペースだったとき
				{
					tokenized_line[tl_index++] = ft_substr(line, line_start_index, 1);
					printf("else if:[%s]\n", tokenized_line[tl_index - 1]);
					line_start_index++;
					// line_index++;
				}
				else
				{
					tokenized_line[tl_index++] = ft_substr(line, line_start_index, line_index - line_start_index);
					printf("else:[%s]\n", tokenized_line[tl_index - 1]);
					line_start_index = line_index;
				}
				flag = 1;
			}
			else
				separator_index++;
		}
		if (line[line_index] != '\0')
			line_index++;
	}
	tokenized_line[tl_index++] = ft_substr(line, line_start_index, line_index - line_start_index);
	tokenized_line[tl_index] = NULL;
	return (tokenized_line);
}

t_ms_ast	*lexer_and_parser(char *str)
{
	char		**tokenized_line;
	char		***splited_pipe;
	t_ms_ast	*ms_ast;

	tokenized_line = tokenize(str);

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
	char 		str[] = "cat file2|grep \"hello\"||||wc -l";//スペースの後ろにセパレータが来るとまずい
	t_ms_ast	*ms_ast;
	char 		**tokenized_line;

	printf("%s\n", str);
	tokenized_line = tokenize(str);

	int i = 0;
	while (tokenized_line[i])
	{
		printf("[%s]\n", tokenized_line[i++]);
	}
	// ms_ast = lexer_and_parser(str);
	return (0);
}
// int main(void)
// {
// 	char	str[100] = "cat>filea|grep\"aa'hello'a\">file2'aaa'hello";
// 	// char		str[50] = "cat -e file | grep 'hello'|wc | tac";
// 	char		**result;
// 	int			i = 0;
// 	t_ms_ast	*ms_ast;
// 	char	***thr_dim_line;

// 	result = tokenize2(str);
// 	printf("[%s]\n", str);
// 	while (result[i])
// 	{
// 		printf("result%2d:[%s]\n", i + 1, result[i]);
// 		i++;
// 	}
// 	// thr_dim_line = dp_to_tp(result);
// 	// ms_ast = pipe_branch(thr_dim_line);
// 	// printf("\n\n\n");
// 	// printf("tac:%s\n", (char *)ms_ast->right_node->cmd_info_list->content);//tac
// 	// printf("wc:%s\n", (char *)ms_ast->left_node->right_node->cmd_info_list->content);//wc
// 	// printf("grep:%s\n", (char *)ms_ast->left_node->left_node->right_node->cmd_info_list->content);//grep
// 	// printf("'hello':%s\n", (char *)ms_ast->left_node->left_node->right_node->cmd_info_list->next->content);//'hello'
// 	// printf("cat:%s\n", (char *)ms_ast->left_node->left_node->left_node->cmd_info_list->content);//cat
// 	// printf("-e:%s\n", (char *)ms_ast->left_node->left_node->left_node->cmd_info_list->next->content);//-e
// 	// printf("file:%s\n", (char *)ms_ast->left_node->left_node->left_node->cmd_info_list->next->next->content);//file
// 	return (0);
// }
