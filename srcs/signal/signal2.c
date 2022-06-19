/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:23:48 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/19 14:02:24 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_after_rl_in_command_read(int not_use)
{
	(void)not_use;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 258;
}

void	sigint_after_rl_in_heredoc(int not_use)
{
	(void)not_use;
	write(STDERR_FILENO, "\n", 1);
	exit(130);
}
