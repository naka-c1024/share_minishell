/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:57:25 by ynakashi          #+#    #+#             */
/*   Updated: 2022/04/30 06:01:56 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	free_darray(char **darray)
{
	size_t	i;

	i = 0;
	while (darray[i])
	{
		free(darray[i]);
		i++;
	}
	free(darray);
}


// static void crawl_ast(t_ms_ast *ms_ast, t_info *info, int i)
// {
// 	if (ms_ast->left_node && ms_ast->type == PIPE)
// 		crawl_ast(ms_ast->left_node, info, ++i);
// 	if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
// 	{
// 		small_ipc_table(info, ms_ast->right_node->cmd_info_list, i);
// 	}
// 	if (ms_ast->cmd_info_list)
// 		small_ipc_table(info, ms_ast->cmd_info_list, info->process_cnt);
// 	return ;
// }

void	executor(t_ms_ast *ms_ast, t_envlist **envlist, char **envp, size_t process_cnt)
{
	char	**two_dim_arr;

	// パイプやリダイレクトの処理の中でonly_one_cmd使う

	// printf("executor-main/34:%zu\n", process_cnt);
	// sort_heredoc_priority(ms_ast);
	g_exit_status = ipc_table(ms_ast, *envlist , envp, process_cnt);
	// printf("%d\n", g_exit_status);
}


//↓↓↓元のexecutor
// void	executor(t_ms_ast *ms_ast, t_envlist **envlist)
// {
// 	char	**two_dim_arr;

// 	// パイプやリダイレクトの処理の中でonly_one_cmd使う

// 	two_dim_arr = lst_to_arr(ms_ast->cmd_info_list);
// 	free_ast(ms_ast);
// 	if (!two_dim_arr)
// 		exit(EXIT_FAILURE);
// 	g_exit_status = only_one_cmd(two_dim_arr, envlist);
// 	free_darray(two_dim_arr);
// }
