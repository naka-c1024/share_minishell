/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:28:42 by ynakashi          #+#    #+#             */
/*   Updated: 2022/03/07 11:28:57 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// ctrl+C
void	sig_int_input()
{
	// ft_putstr_fd("\b\b  \b\n", STDERR_FILENO);
	// ft_putstr_fd("ctrl+C", STDERR_FILENO);
	write(STDERR_FILENO, "ctrl+C\n", 7);
}
// "ctrl+\"
void	sig_quit_input()
{
	// ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
	// ft_putstr_fd("ctrl+\\", STDERR_FILENO);
	write(STDERR_FILENO, "ctrl+\\\n", 7);
}

int	main(int argc, char **argv, char **envp)
{
	char	*command;
	char	*exe_arg[2];

	pid_t pid;
	int status;
	int ret;

	while (1)
	{
		// signal処理
		if (signal(SIGINT, sig_int_input) == SIG_ERR)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			exit (EXIT_FAILURE);
		}
		if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			exit (EXIT_FAILURE);
		}
		// 入力受付
		command = readline("absolute path -> ");
		if (command && ft_strlen(command) > 0)
		{
			if (ft_strncmp(command, "exit", 5) == 0)
			{
				write(STDERR_FILENO, "exit\n", 5);
				free(command);
				return (EXIT_SUCCESS);
				// break ;
			}
			// builtin funcの処理
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				free(command);
				return (EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				exe_arg[0] = command;
				exe_arg[1] = NULL;
				if (execve(command, exe_arg, envp) == -1)
				{
					printf("bash: %s: command not found\n", command);
					// free(command);
					return (EXIT_FAILURE);
				}
			}
			else
			{
				ret = wait(&status);
				if (ret < 0)
				{
					perror("wait");
					free(command);
					return (EXIT_FAILURE);
				}
			}
			// 履歴の付け足し
			add_history(command);
		}
		free(command);
	}
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}

// char	*get_line()
// {
// 	char *line;

// 	line = NULL;
// 	if (line)
// 	{
// 		free(line);
// 		line = NULL;
// 	}
// 	line = readline("Minishell>");
// 	if (line)
// 		add_history(line);
// 	return (line);
// }

// void	sig_handler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_replace_line("", 0); // 入力されたものをリセット
// 		rl_on_new_line(); // 次の行に移動
// 		rl_redisplay(); // -再表示して以上の操作を画面上に反映
// 	}
// }

// int main(void)
// {
// 	char	*line;

// 	signal(SIGINT, sig_handler);
// 	line = get_line();
// 	printf("%s\n", line);
// }
