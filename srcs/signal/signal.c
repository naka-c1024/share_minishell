/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:01:56 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/11 15:06:00 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctrl+C
void	sigint_before_rl(int not_use)
{
	(void)not_use;

	write(STDOUT_FILENO, "\n", 1);
	// rl_replace_line("", 0); // 入力されたものをclear, m1macだとコンパイルできないためコメントアウトしている
	rl_on_new_line(); // 次の行に移動
	rl_redisplay(); // -再表示して以上の操作を画面上に反映
}

void	sigint_after_rl(int not_use)
{
	(void)not_use;

	exit(EXIT_FAILURE);
}
// "ctrl+\"
void	sigquit_after_rl(int not_use)
{
	(void)not_use;
	exit(EXIT_FAILURE);
}

void	init_signal(int sig_num, void (*func)(int not_use))
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = func;
	if (sigaction(sig_num, &act, NULL) == -1)
		exit (EXIT_FAILURE);
}