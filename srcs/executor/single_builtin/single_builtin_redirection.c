/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_builtin_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:27:46 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/03 16:40:51 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_twod_array(char **darray)
{
	size_t	i;

	i = 0;
	if (!darray)
		return ;
	while (darray[i])
	{
		free(darray[i]);
		i++;
	}
	free(darray);
}

t_list	*ms_lstnew(char *content)
{
	t_list	*new_element;

	if (!content)
		return (NULL);
	new_element = (t_list *)x_malloc(sizeof(t_list));
	if (!new_element)
		return (NULL);
	new_element->content = ft_x_strdup(content);
	if (!new_element->content)
	{
		free(new_element);
		return (NULL);
	}
	new_element->next = NULL;
	return (new_element);
}

void	dup_and_close(t_process_info *proc_info)
{
	if (!proc_info->is_here_doc \
		&& !proc_info->file_info->in_file && !proc_info->file_info->out_file)
		return ;
	if (proc_info->file_info->in_file)
	{
		proc_info->file_info->tmp_stdin = dup(STDIN);
		dup2(proc_info->file_info->in_fd, STDIN);
	}
	if (proc_info->file_info->out_file)
	{
		proc_info->file_info->tmp_stdout = dup(STDOUT);
		dup2(proc_info->file_info->out_fd, STDOUT);
	}
}

void	restore_redirection(t_process_info *proc_info)
{
	if (proc_info->file_info->in_file)
	{
		dup2(proc_info->file_info->tmp_stdin, STDIN);
		close(proc_info->file_info->tmp_stdin);
		close(proc_info->file_info->in_fd);
	}
	if (proc_info->file_info->out_file)
	{
		dup2(proc_info->file_info->tmp_stdout, STDOUT);
		close(proc_info->file_info->tmp_stdout);
		close(proc_info->file_info->out_fd);
	}
}
