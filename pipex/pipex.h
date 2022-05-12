/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:19:50 by kahirose          #+#    #+#             */
/*   Updated: 2022/03/11 18:25:57 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include "../libft/libft.h"

# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define PIPEIN 0
# define PIPEOUT 1
# define NOFILE -2
# define FD_MAX 256
# define PATH_PREFIX 5

typedef struct s_info
{
	int		**pipefd;
	int		argc;
	int		process_cnt;
	char	**argv;
	char	**envp;
	char	**cmd_full_path;
	char	***cmd;
	char	*file;
	bool	is_here_doc;
	char	*total_document;
	char	*limiter;
	pid_t	*pid;
	int		error_status;
	int		first_cmd_index;
}	t_info;

bool	is_valid_start_file(t_info info);
bool	is_valid_cmds(t_info info);
void	convert_to_cmd_full_path(t_info *info, int i);
char	*get_next_line(int fd);
void	*free_one(char **s);
void	*free_all(char **s1, char **s2);
int		start_process(t_info info);
void	close_func(t_info *info, int filefd, int cmd_index);
void	dup2_func(t_info *info, int filefd, int cmd_index);
int		get_filefd(t_info *info, int cmd_index);
int		error_handler(void);
int		free_all_info(t_info *info, bool error, int error_status);
void	free_2arr(void ***arr);
int		safe_func(int res, t_info *info);
ssize_t	pipex_putstr(char *s, int fd);

#endif
