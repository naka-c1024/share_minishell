/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:01:56 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/18 11:27:45 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ctrl+C
void	sigint_before_rl(int not_use)
{
	(void)not_use;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 1;
}

void	sigint_after_rl_in_heredoc(int not_use)
{
	(void)not_use;
	write(STDERR_FILENO, "\n", 1);
	exit(130);
}

void	sigint_after_rl(int not_use)
{
	(void)not_use;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 130;
}

// "ctrl+\"
void	sigquit_after_rl(int not_use)
{
	(void)not_use;
	write(STDERR_FILENO, "Quit: 3\n", 8);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 131;
}

void	init_signal(int sig_num, void (*func)(int not_use))
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = func;
	if (sigaction(sig_num, &act, NULL) == -1)
		exit (EXIT_FAILURE);
}
