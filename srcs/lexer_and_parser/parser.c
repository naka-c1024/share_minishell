#include "minishell.h"

static int	token_counter(char **cmd_line_start)
{
	int	count;

	count = 0;
	while (cmd_line_start[count] && cmd_line_start[count][0] != '|')
		count++;
	return (count);
}

char	***split_by_pipe(char **cmd_line)
{
	char	***result;
	int		idx;
	int		counter;
	int		res_i;
	int		res_j;
	int		token_cnt;

	idx = 0;
	counter = 1;
	while (cmd_line[idx])
	{
		if (cmd_line[idx][0] == '|')
			counter++;
		idx++;
	}
	// printf("counter:%d\n", counter);
	result = (char ***)malloc(sizeof(char **) * (counter * 2));
	idx = 0;
	res_i = 0;
	while (cmd_line[idx])
	{
		res_j = 0;
		if (cmd_line[idx][0] != '|')
		{
			token_cnt = token_counter(&(cmd_line[idx]));
			result[res_i] = (char **)malloc(sizeof(char *) * (token_cnt + 1));
			if (!result[res_i])
			{
				;
			}
			while (cmd_line[idx] && cmd_line[idx][0] != '|')
			{
				result[res_i][res_j] = ft_strdup(cmd_line[idx]);
				if (!result[res_i][res_j])
				{
					;
				}
				idx++;
				res_j++;
			}
			result[res_i][res_j] = NULL;
			res_i++;
		}
		else
		{
			result[res_i] = (char **)malloc(sizeof(char *) * 2);
			result[res_i][0] = ft_strdup(cmd_line[idx++]);
			result[res_i][1] = NULL;
			if (!result[res_i][res_j])
			{
				;
			}
			res_i++;
		}
	}
	result[res_i] = NULL;
	//このあたりでcmd_lineをfree
	return (result);
}

// int main(void)
// {
// 	char		**str;
// 	t_ms_ast	*ms_ast;

// 	str = (char **)malloc(sizeof(char *) * (10 + 1));
// 	str[0] = ft_strdup("cat");
// 	str[1] = ft_strdup("-e");
// 	str[2] = ft_strdup("file");
// 	str[3] = ft_strdup("|");
// 	str[4] = ft_strdup("'hello'");
// 	str[5] = ft_strdup("|");
// 	str[6] = ft_strdup("wc");
// 	str[7] = ft_strdup("|");
// 	str[8] = ft_strdup("tac");
// 	str[9] = NULL;

// 	// int idx = 0;
// 	// while (str[idx])
// 	// {
// 	// 	printf("[%s]\n", str[idx]);
// 	// 	idx++;
// 	// }

// 	char	***thr_dim_line;
// 	thr_dim_line = dp_to_tp(str);
// 	// int i = 0;
// 	// int j = 0;
// 	// while (thr_dim_line[i])
// 	// {
// 	// 	j = 0;
// 	// 	while (thr_dim_line[i][j])
// 	// 	{
// 	// 		printf("[%s]", thr_dim_line[i][j]);
// 	// 		j++;
// 	// 	}
// 	// 	printf("\n");
// 	// 	i++;
// 	// }
// 	ms_ast = pipe_branch(thr_dim_line);
// 	printf("%s\n", (char *)ms_ast->right_node->cmd_info_list->content);
// 	printf("%s\n", (char *)ms_ast->left_node->right_node->cmd_info_list->content);
// 	printf("%s\n", (char *)ms_ast->left_node->left_node->right_node->cmd_info_list->content);
// 	printf("%s\n", (char *)ms_ast->left_node->left_node->left_node->cmd_info_list->content);
// 	printf("%s\n", (char *)ms_ast->left_node->left_node->left_node->cmd_info_list->next->content);
// 	printf("%s\n", (char *)ms_ast->left_node->left_node->left_node->cmd_info_list->next->next->content);

// 	return (0);
// }
