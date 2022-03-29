/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:23:54 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/28 14:35:06 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../../libft/libft.h"

# include <readline/readline.h> // readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <stdlib.h> // malloc, free, exit, getenv
# include <signal.h> // signal, sigaction, sigemptyset, sigaddset, kill

// # include <limits.h> // macro
// # include <stdint.h> // macro(linux)
// # include <stdbool.h> // bool
// # include <errno.h> // errno

void	sigint_before_rl(int not_use);
void	sigint_after_rl(int not_use);
void	sigquit_after_rl(int not_use);
void	init_signal(int sig_num, void (*func)(int not_use));

#endif // SIGNAL_H
