/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:34:57 by ynakashi          #+#    #+#             */
/*   Updated: 2022/06/19 12:19:53 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../libft/libft.h"
# include "../../includes/minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define PIPEIN 0
# define PIPEOUT 1
# define NOFILE -2
# define FD_MAX 256
# define PATH_PREFIX 4
# define IN 1
# define HERE 2
# define OUT 3
# define PIPE 1
# define SINGLE_QUOTE 2
# define DOUBLE_QUOTE 3
# define MY_EXIT 0
# define MY_ECHO 1
# define MY_CD 2
# define MY_PWD 3
# define MY_UNSET 4
# define MY_ENV 5
# define MY_EXPORT 6

typedef struct s_file_info
{
	bool	in_file;
	bool	out_file;
	int		in_redirect;
	int		out_redirect;
	int		in_fd;
	int		out_fd;
	int		tmp_stdin;
	int		tmp_stdout;
}	t_file_info;

typedef struct s_heredoc_info
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

void			free_list(t_envlist *list);
void			ms_lstadd_back(t_envlist **lst, t_envlist *element);
int				my_cd(char **split_ln, t_envlist **envlist);
int				my_echo(char **split_ln);
int				my_env(t_envlist *envlist);
int				my_exit(char **split_ln);
void			numeric_argument_required(char *str);
void			remove_duplicate(char *str, t_envlist **envlist);
int				my_export(char **split_ln, t_envlist **envlist);
char			**list_to_darray(t_envlist *envlist);
void			print_export(t_envlist *envlist);
bool			can_export(char *str);
bool			is_equal(char *str);
int				no_equal(char *str, t_envlist **envlist);
void			not_a_valid_identifier(char *str);
int				my_pwd(void);
int				my_unset(char **split_ln, t_envlist **envlist);
int				ipc_table(t_ms_ast *ms_ast, \
				t_envlist *envlist, size_t process_cnt);
char			**create_env_arr(t_envlist *envlist);
void			free_info(t_info **info);
void			free_process_info(t_process_info **proc_info_addr);
void			child_exe(t_info *info, \
				t_process_info *p_info, t_ms_ast *ast_node);
char			**lst_to_arr(t_list *arglst);
void			convert_to_cmd_full_path(t_info *info, t_process_info *p_info);
void			redirection_sequence(t_ms_ast *ast_node, \
				t_process_info *p_info);
void			set_out_file(t_process_info *proc_info, \
				char *file_name, int redirect_type);
void			set_in_file(t_process_info *proc_info, char *file_name);
void			set_heredoc(t_ms_ast *ast_node, t_process_info *proc_info);
void			dup2_func(t_info *info, t_process_info *p_info);
void			close_func(t_info *info, t_process_info *p_info);
void			heredoc_dup2(t_info *info, t_process_info *proc_info);
void			heredoc_close(t_info *info, t_process_info *proc_info);
ssize_t			pipex_putstr(char *s);
void			free_process_info(t_process_info **proc_info_addr);
t_list			*ms_lstnew(char *content);
bool			only_builtin_assign_func(char builtin_list[7][7], \
				t_ms_ast *ms_ast, char *cmd_name, t_envlist **envlist);
t_process_info	*serch_redirection(t_ms_ast *ms_ast, bool *is_success);
void			dup_and_close(t_process_info *proc_info);
void			restore_redirection(t_process_info *proc_info);
void			free_twod_array(char **darray);
bool			sb_set_in_file(t_process_info *proc_info, char *file_name);
bool			sb_set_out_file(t_process_info *proc_info, \
				char *file_name, int redirect_type);
bool			sb_set_heredoc(t_ms_ast *ast_node, t_process_info *proc_info);
int				is_some_redirect(char *one_token);

#endif
