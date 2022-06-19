/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 22:00:04 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/18 22:22:58 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc_input.h"

void	receive_buffer(t_ms_ast *ms_ast, int pipefd[2])
{
	char	*temp1;
	char	*temp2;
	int		read_flag;

	read_flag = 0;
	ms_ast->buffer = ft_x_strdup("");
	while (1)
	{
		temp1 = ms_ast->buffer;
		temp2 = (char *)ft_x_calloc(101, sizeof(char));
		read_flag = safe_func(read(pipefd[0], temp2, 100));
		if (read_flag == 0)
		{
			free(temp2);
			return ;
		}
		ms_ast->buffer = ft_x_strjoin(temp1, temp2);
		free(temp1);
		free(temp2);
	}
}
