/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 05:15:44 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 05:41:28 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//static void	envlist_clear(t_envlist *stack)
//{
	//if (stack)
		//envlist_clear(stack->next);
	//free(stack);
//}

static void	free_pipefd(int **pipefd, int process_cnt)
{
	size_t	idx;

	idx = 0;
	while (process_cnt > 0)
	{
		free(pipefd[idx++]);
		process_cnt--;
	}
	free(pipefd);
}

void	free_info(t_info **info)
{
	if (!*info)
		return ;
	if ((*info)->envp)
		free_two_d_arr((*info)->envp);
	if ((*info)->ms_ast)
		free_ast((*info)->ms_ast);
	if ((*info)->ms_ast)
		free_pipefd((*info)->pipefd, (*info)->process_cnt);
	free((*info)->pid);
	free(*info);
	*info = NULL;
}

void	free_process_info(t_process_info **proc_info_addr)
{
	if (!proc_info_addr || !(*proc_info_addr))
		return ;
	if ((*proc_info_addr)->cmd_list)
		list_clear((*proc_info_addr)->cmd_list);
	if ((*proc_info_addr)->hrdc_info)
		free((*proc_info_addr)->hrdc_info);
	if ((*proc_info_addr)->file_info)
		free((*proc_info_addr)->file_info);
	free(*proc_info_addr);
	*proc_info_addr = NULL;
}
