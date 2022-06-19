/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:18:11 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/18 22:18:35 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_INPUT_H
# define HERE_DOC_INPUT_H

# include "minishell.h"
# include "../../libft/libft.h"

size_t	get_here_doc_init(t_ms_ast *ms_ast, char *delimiter);
size_t	make_buffer(t_ms_ast *ms_ast, char *delimiter);
void	receive_buffer(t_ms_ast *ms_ast, int pipefd[2]);

#endif
