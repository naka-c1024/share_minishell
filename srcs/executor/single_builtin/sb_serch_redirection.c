/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_serch_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:41:46 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/09 01:54:40 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_some_redirect(char *one_token)
{
	if (!ft_strncmp(one_token, "<<", 2))
		return (HERE);
	else if (!ft_strncmp(one_token, ">>", 2))
		return (4);
	if (!ft_strncmp(one_token, "<", 1))
		return (IN);
	else if (!ft_strncmp(one_token, ">", 1))
		return (OUT);
	return (0);
}

bool	set_redirect_info(t_ms_ast *ms_ast, t_process_info *proc_info, \
										t_list **list, int redirect_type)
{
	bool	is_success;

	if (redirect_type == IN)
		is_success = sb_set_in_file(proc_info, (*list)->next->content);
	else if (redirect_type == HERE)
		is_success = sb_set_heredoc(ms_ast, proc_info);
	else
		is_success = sb_set_out_file \
			(proc_info, (*list)->next->content, redirect_type);
	*list = (*list)->next;
	if (*list)
		*list = (*list)->next;
	return (is_success);
}

t_process_info	*serch_redirection(t_ms_ast *ms_ast, bool *is_success)
{
	int				redirect_type;
	t_list			*list;
	t_process_info	*proc_info;

	proc_info = (t_process_info *)ft_x_calloc(1, sizeof(t_process_info));
	proc_info->file_info = (t_file_info *)ft_x_calloc(1, sizeof(t_file_info));
	list = ms_ast->cmd_info_list;
	while (list && *is_success)
	{
		redirect_type = is_some_redirect(list->content);
		if (redirect_type != 0)
		{
			*is_success = set_redirect_info \
				(ms_ast, proc_info, &list, redirect_type);
		}
		else
		{
			ft_lstadd_back(&(proc_info->cmd_list), ms_lstnew(list->content));
			list = list->next;
		}
	}
	return (proc_info);
}
