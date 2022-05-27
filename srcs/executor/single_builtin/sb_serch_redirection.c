/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_serch_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:41:46 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/24 14:12:31 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	is_some_redirect(char *one_token)
{
	if (!ft_strncmp(one_token, "<<", 2))
		return (2);
	else if (!ft_strncmp(one_token, ">>", 2))
		return (4);
	if (!ft_strncmp(one_token, "<", 1))
		return (1);
	else if (!ft_strncmp(one_token, ">", 1))
		return (3);
	return (0);
}

t_process_info	*serch_redirection(t_ms_ast *ms_ast)
{
	int				redirect_type;
	t_list			*list;
	t_process_info	*proc_info;

	proc_info = (t_process_info *)ft_calloc(1, sizeof(t_process_info));
	if (!proc_info)
		return (NULL);
	proc_info->file_info = (t_file_info *)ft_calloc(1, sizeof(t_file_info));
	if (!proc_info->file_info)
		return (NULL);
	list = ms_ast->cmd_info_list;
	while (list)
	{
		redirect_type = is_some_redirect(list->content);
		if (redirect_type != 0)
		{
			if (redirect_type == 1)
				sb_set_in_file(proc_info, list->next->content);
			else if (redirect_type == 2)
				sb_set_heredoc(ms_ast, proc_info);
			else
				sb_set_out_file(proc_info, list->next->content, redirect_type);
			list = list->next;
			if (list)
				list = list->next;
		}
		else
		{
			ft_lstadd_back(&(proc_info->cmd_list), ms_lstnew(list->content));
			list = list->next;
		}
	}
	return (proc_info);
}
