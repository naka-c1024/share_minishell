/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:37:04 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/18 08:25:33 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../includes/minishell.h"

// expand_dollar.c
void	expand_dollar(char **str, t_envlist *envlist);

// expand_quote.c
void	expand_single(char **str);
void	expand_double(char **str, t_envlist *envlist);

#endif /* EXPANDER_H */
