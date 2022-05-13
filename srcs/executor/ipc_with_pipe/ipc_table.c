/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:30 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/13 17:14:39 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_darray(void **array)
{
	size_t	idx;

	idx = 0;
	while (array[idx])
		free(array[idx++]);
	free(array[idx]);
	free(array);
}

void	free_p_info(t_process_info **p_info)
{
	free((*p_info)->cmd_full_path);
	free_darray((void **)(*p_info)->cmd);
	// free((*p_info)->file);
}

void	envlist_clear(t_envlist *stack)
{
	if (stack)
		envlist_clear(stack->next);
	free(stack);
}

void	free_pipefd(int **pipefd, int process_cnt)
{
	size_t	idx;

	idx = 0;
	while (process_cnt > 0)//条件はプロセスカウント持ってきて使った方が良さそう
	{
		free(pipefd[idx++]);
		process_cnt--;
	}
	//int型配列でNULL止めしてないため最後のインデックスフリーはいらない
	free(pipefd);
}

void	free_info(t_info **info)
{
	if (!*info)
		return ;
	//if ((*info)->envlist)
		//envlist_clear((*info)->envlist);
	if ((*info)->envp)
		;//free_darray((*info)->envp);
	if ((*info)->ms_ast)
		free_ast((*info)->ms_ast);
	if ((*info)->ms_ast)
		free_pipefd((*info)->pipefd, (*info)->process_cnt);
	free((*info)->pid);
	free(*info);
	*info = NULL;
}

size_t	envlist_len(t_envlist *envlist)
{
	size_t	len;

	len = 0;
	while(envlist)
	{
		len++;
		envlist = envlist->next;
	}
	return (len);
}

char	**create_env_arr(t_envlist *envlist)
{
	char	**env_arr;
	size_t	idx;

	env_arr = (char **)ft_calloc(envlist_len(envlist) + 1, sizeof(t_envlist));
	if (!env_arr)
		return (NULL);
	idx = 0;
	while (envlist)
	{
		env_arr[idx] = ft_strjoin(envlist->key, envlist->value);
		envlist = envlist->next;
		idx ++;
	}
	return (env_arr);
}

void	small_ipc_table(t_info *info, t_ms_ast *ast_node, int i)
{
	t_process_info	*p_info;

	p_info = (t_process_info *)ft_calloc(1, sizeof(t_process_info));
	p_info->section = info->process_cnt - i;
	if (p_info->section + 1 != info->process_cnt && \
					pipe(info->pipefd[p_info->section]) < 0)
		exit (1);// exit(free_all_info(info, true, 1));
	info->pid[p_info->section] = fork();
	if (info->pid[p_info->section] == -1)
		exit (1);// exit(free_all_info(info, true, 1));
	else if (info->pid[p_info->section] == 0)
		child_exe(info, p_info, ast_node);
	else
	{
		if (p_info->section != 0)
		{
			safe_func(close(info->pipefd[p_info->section - 1][0]), info);
			safe_func(close(info->pipefd[p_info->section - 1][1]), info);
		}
	}
	// free_p_info(&p_info);
}

static void crawl_ast_in_ipc_table(t_ms_ast *ms_ast, t_info *info, int i)
{
	if (ms_ast->left_node && ms_ast->type == PIPE)
		crawl_ast_in_ipc_table(ms_ast->left_node, info, ++i);
	if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
	{
		small_ipc_table(info, ms_ast->right_node, i);
	}
	if (ms_ast->cmd_info_list)
	{
		small_ipc_table(info, ms_ast, info->process_cnt);
	}
	return ;
}

int	ipc_table(t_ms_ast *ms_ast, t_envlist *envlist, size_t process_cnt)
{
	t_info	*info;
	int		wstatus;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	info->envlist = envlist;
	info->envp = create_env_arr(envlist);
	info->ms_ast = ms_ast;
	info->process_cnt = process_cnt;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * info->process_cnt);
	info->pipefd = (int **)ft_calloc(info->process_cnt, sizeof(int *));
	int i = 0;
	while (i < info->process_cnt)
		info->pipefd[i++] = (int *)ft_calloc(2, sizeof(int));
	crawl_ast_in_ipc_table(ms_ast, info, 0);
	i = 0;
	while (i < info->process_cnt)
	{
		// printf("%d\n", info->pid[i]);
		safe_func(waitpid(info->pid[i], &wstatus, WUNTRACED), info);
		i++;
	}
	free_info(&info);
	return (WEXITSTATUS(wstatus));
}

// t_ms_ast	*lexer_and_parser(char *str, t_info *info)
// {
// 	char		**tokenized_line;
// 	char		***splited_pipe;
// 	t_ms_ast	*ms_ast;

// 	tokenized_line = tokenize_main(str);
// 	if (!tokenized_line)
// 		;
// 	// print_tokenized_line(tokenized_line);
// 	splited_pipe = split_by_pipe(tokenized_line);
// 	if (!splited_pipe)
// 		;
// 	// print_sbp(splited_pipe);
// 	ms_ast = make_ast(splited_pipe);
// 	if (!ms_ast)
// 		;
// 	// printf("\n↓print_ast\n\n");
// 	// print_ast(ms_ast);
// 	return (ms_ast);
// }


// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q lexer_and_parser");
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	// char 		str[] = "<cat file2|grep \"he' ohayo-'llo\"||||wc -l  ><<< > file2 >";
// 	// char		str[] = ">>ls |<<| cat file2 >> file3|| grep -i  \"first\" | wc -l >> outfile";
// 	// char		str[] = "cat ipc_executor.c | head -n20 | tail -n10";
// 	char	str[] = "cat lexer_and_parser.h | wd | head -n 20 | cat Makefile";
// 	// char 	str[] = "cat | cat | cat | ls";
// 	// char		str[] = "export TEST=\"hello\"";
// 	// char 		str[] = "";
// 	char 		**tokenized_line;
// 	t_ms_ast	*ms_ast;
// 	size_t		tl_len;
// 	t_envlist	*envlist;

// 	//引数使用
// 	argc = 0;
// 	argv = NULL;

// 	// printf("source_line:[%s]\n", str);
// 	t_info *info;
// 	ms_ast = lexer_and_parser(str, info);
// 	if (!ms_ast)
// 		return (0);
// 	// system("leaks -q lexer_and_parser");
// 	envlist = create_envlist(envp);
// 	int	exit_status;
// 	exit_status = executor_test(ms_ast, envlist, envp);
// 	printf("\n\n[$?=%d]\n", exit_status);
// 	free_ast(ms_ast);
// 	// system("leaks -q lexer_and_parser");
// 	return (0);
// }

//パイプが最初or最後にあればsyntax_error
//クォーとが偶数子でなかった場合
//パイプが二つ続く場合
//リダイレクト関係
// < |
