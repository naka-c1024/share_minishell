/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:34:57 by ynakashi          #+#    #+#             */
/*   Updated: 2022/05/12 04:26:41 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../libft/libft.h"
# include "../../includes/minishell.h"

// extern int	g_exit_status;

# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc, free, exit, getenv
# include <unistd.h> // write, access, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <string.h> // strerror

# include <limits.h> // macro
# include <stdint.h> // macro(linux)
# include <stdbool.h> // bool
# include <errno.h> // errno

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define PIPEIN 0
# define PIPEOUT 1
# define NOFILE -2
# define FD_MAX 256
# define PATH_PREFIX 4

// typedef struct s_info
// {
// 	char		**envp;
// 	t_envlist	*envlist;
// 	t_ms_ast	*ms_ast;
// 	int			**pipefd;
// 	pid_t		*pid;//何に使うの？
// 	int			process_cnt;
// }	t_info;

typedef struct s_file_info
{
	// char	*in_file;
	// char	*out_file;
	bool	in_file;
	bool	out_file;
	int		in_redirect;
	int		out_redirect;
	int		in_fd;
	int		out_fd;
}	t_file_info;

typedef	struct s_heredoc_info
{
	int		*here_doc_pipe;
	bool	is_here_doc;
	char	*buffer;
	char	*delimiter;
}	t_heredoc_info;

typedef struct s_process_info
{
	t_list			*cmd_list;
	char			*cmd_full_path;
	char			**cmd;
	int				section;
	t_file_info		*file_info;
	bool			is_here_doc;
	t_heredoc_info	*hrdc_info;
}	t_process_info;

// envlist.c
void		free_list(t_envlist *list);
void		ms_lstadd_back(t_envlist **lst, t_envlist *element);
// t_envlist	*create_envlist(char **envp);

// cd.c
int		my_cd(char **split_ln, t_envlist **envlist);

// echo.c
int		my_echo(char **split_ln);

// env.c
int		my_env(t_envlist *envlist);

// exit.c
int		my_exit(char **split_ln);

// exit_utils.c
void	numeric_argument_required(char *str);

// export.c
void	remove_duplicate(char *str, t_envlist **envlist);
int		my_export(char **split_ln, t_envlist **envlist);

// pwd.c
int		my_pwd(void);

// unset.c
int		my_unset(char **split_ln, t_envlist **envlist);

// no_builtin.c
int	exe_no_builtin_cmd(char **str, t_envlist *envlist);

// only_one_cmd.c
int	only_one_cmd(char **dbl_arr, t_envlist **envlist);

//ipc_with_pipe
int		ipc_table(t_ms_ast *ms_ast, t_envlist *envlist, char **envp, size_t process_cnt);
void	child_exe(t_info *info, t_process_info *p_info, t_ms_ast *ast_node);
char	**lst_to_arr(t_list *arglst);
void	convert_to_cmd_full_path(t_info *info, t_process_info *p_info);
void	redirection_seqence(t_ms_ast *ast_node, t_process_info *p_info, t_info *info);
void	dup2_func(t_info *info, t_process_info *p_info);
void	close_func(t_info *info, t_process_info *p_info);
void	heredoc_dup2(t_info *info, t_process_info *proc_info);
void	heredoc_close(t_info *info, t_process_info *proc_info);
int		safe_func(int res, void *info);

#endif // EXE_CMD_H
