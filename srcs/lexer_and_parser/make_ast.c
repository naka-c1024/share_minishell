#include "minishell.h"

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
