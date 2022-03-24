#include "../includes/minishell.h"

t_ms_ast	*new_pipe_node(t_ms_ast *left, t_ms_ast *right)
{
	t_ms_ast	*ms_pipe_node;

	ms_pipe_node = (t_ms_ast *)malloc(sizeof(t_ms_ast));
	if (!ms_pipe_node)
	{
		;
	}
	ms_pipe_node->type = PIPE;
	ms_pipe_node->left_node = left;
	ms_pipe_node->right_node = right;
	return (ms_pipe_node);
}

static t_list	*make_cmd_list(char ****all_cmd_line_addr)
{
	t_list	*new_node;
	t_list	*list;

	list = ft_lstnew((*all_cmd_line_addr)[0][0]);
	if (!list)
	{
		;
	}
	(*all_cmd_line_addr)[0]++;//これすると次の条件文でセグフォする可能性ないか？
	while ((*all_cmd_line_addr)[0][0] != NULL)
	{
		// printf("28:%s\n", (*all_cmd_line_addr)[0][0]);
		new_node = ft_lstnew((*all_cmd_line_addr)[0][0]);
		if (!new_node)
		{
			;
		}
		ft_lstadd_back(&list, new_node);
		(*all_cmd_line_addr)[0]++;
	}
	return (list);
}

t_ms_ast	*new_cmd_node(char ****all_cmd_line_addr)
{
	t_ms_ast	*ms_cmd_node;

	ms_cmd_node = (t_ms_ast *)malloc(sizeof(t_ms_ast));
	if (!ms_cmd_node)
	{
		;
	}
	ms_cmd_node->type = COMMAND;
	ms_cmd_node->cmd_info_list = make_cmd_list(all_cmd_line_addr);
	ms_cmd_node->left_node = NULL;
	ms_cmd_node->right_node = NULL;
	(*all_cmd_line_addr)++;
	return (ms_cmd_node);
}
