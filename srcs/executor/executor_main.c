/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 20:57:25 by ynakashi          #+#    #+#             */
/*   Updated: 2022/05/13 18:44:29 by kahirose         ###   ########.fr       */
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

void	single_builtin_only(t_ms_ast *ms_ast, t_envlist **envlist, int cmd_type)
{
	char	**two_dim_arr;

	//redirection_seqence()
	two_dim_arr = lst_to_arr(ms_ast->cmd_info_list);
	if (cmd_type == MY_EXIT)
		g_exit_status = my_exit(two_dim_arr);
	else if (cmd_type == MY_ECHO)
		g_exit_status = my_echo(two_dim_arr);
	else if (cmd_type == MY_CD)
		g_exit_status = my_cd(two_dim_arr, envlist);
	else if (cmd_type == MY_PWD)
		g_exit_status = my_pwd();
	else if (cmd_type == MY_UNSET)
		g_exit_status = my_unset(two_dim_arr, envlist);
	else if (cmd_type == MY_ENV)
		g_exit_status = my_env(*envlist);
	else
		g_exit_status = my_export(two_dim_arr, envlist);
}

void	executor(t_ms_ast *ms_ast, t_envlist **envlist, size_t process_cnt)
{
	char	**two_dim_arr;

	// パイプやリダイレクトの処理の中でonly_one_cmd使う

	// printf("executor-main/34:%zu\n", process_cnt);
	// sort_heredoc_priority(ms_ast);
	if (ms_ast->type == COMMAND)
	{
		two_dim_arr = lst_to_arr(ms_ast->cmd_info_list);
		if (ft_strncmp(two_dim_arr[0], "exit", 5) == 0)
			single_builtin_only(ms_ast, envlist, MY_EXIT);
		else if (ft_strncmp(two_dim_arr[0], "echo", 5) == 0)
			single_builtin_only(ms_ast, envlist, MY_ECHO);
		else if (ft_strncmp(two_dim_arr[0], "cd", 3) == 0)
			single_builtin_only(ms_ast, envlist, MY_CD);
		else if (ft_strncmp(two_dim_arr[0], "pwd", 4) == 0)
			single_builtin_only(ms_ast, envlist, MY_PWD);
		else if (ft_strncmp(two_dim_arr[0], "unset", 6) == 0)
			single_builtin_only(ms_ast, envlist, MY_UNSET);
		else if (ft_strncmp(two_dim_arr[0], "env", 4) == 0)
			single_builtin_only(ms_ast, envlist, MY_ENV);
		else if (ft_strncmp(two_dim_arr[0], "export", 7) == 0)
			single_builtin_only(ms_ast, envlist, MY_EXPORT);
		else
			ipc_table(ms_ast, *envlist, process_cnt);
	}
	else
	{
		g_exit_status = ipc_table(ms_ast, *envlist, process_cnt);
	}
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
// 		EXIT_FAILURE);
// 	g_exit_status = only_one_cmd(two_dim_arr, envlist);
// 	free_darray(two_dim_arr);
// }
