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

// 	// int tl_i = 0;
// 	// while (str[tl_i])
// 	// {
// 	// 	printf("[%s]\n", str[tl_i]);
// 	// 	tl_i++;
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
