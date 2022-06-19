/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:56:43 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/18 22:29:07 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc_input.h"

size_t	get_here_doc_init(t_ms_ast *ms_ast, char *delimiter)
{
	size_t	len;

	free(ms_ast->buffer);
	free(ms_ast->delimiter);
	ms_ast->buffer = ft_x_strdup("");
	len = ft_strlen(delimiter);
	ms_ast->delimiter = (char *)ft_x_calloc(len + 1, sizeof(char));
	ft_strlcpy(ms_ast->delimiter, delimiter, len + 1);
	ms_ast->delimiter[len] = '\n';
	return (len);
}

static char	*make_buffer_init(void)
{
	char	*a_temp;
	char	*b_temp;

	b_temp = readline("> ");
	if (!b_temp)
		return (NULL);
	a_temp = ft_x_strjoin(b_temp, "\n");
	free(b_temp);
	return (a_temp);
}

size_t	make_buffer(t_ms_ast *ms_ast, char *delimiter)
{
	size_t	len;
	char	*a_temp;
	char	*b_temp;
	char	*new_document;

	ms_ast->is_here_doc = true;
	len = get_here_doc_init(ms_ast, delimiter);
	a_temp = make_buffer_init();
	if (!a_temp)
		return (0);
	while (ft_strncmp(a_temp, ms_ast->delimiter, len + 1))
	{
		new_document = ft_x_strjoin(ms_ast->buffer, a_temp);
		free(ms_ast->buffer);
		free(a_temp);
		ms_ast->buffer = new_document;
		b_temp = readline("> ");
		if (!b_temp)
			return (0);
		a_temp = ft_x_strjoin(b_temp, "\n");
		free(b_temp);
	}
	free(a_temp);
	return (ft_strlen(ms_ast->buffer));
}
