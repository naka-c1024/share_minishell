/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 07:34:41 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/18 07:36:06 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

bool	is_quote(t_tokenize_info *t_info)
{
	if (t_info->line[*(t_info->line_index)] == '\'' || \
		t_info->line[*(t_info->line_index)] == '"')
		return (true);
	return (false);
}

bool	is_single_redirect(t_tokenize_info *t_info)
{
	if (t_info->line[*(t_info->line_index)] == '>' || \
		t_info->line[*(t_info->line_index)] == '<')
		return (true);
	return (false);
}

bool	is_double_redirect(t_tokenize_info *t_info)
{
	if (!ft_strncmp(&(t_info->line[*(t_info->line_index)]), ">>", 2) || \
		!ft_strncmp(&(t_info->line[*(t_info->line_index)]), "<<", 2))
		return (true);
	return (false);
}
