/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:51:30 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/24 11:09:33 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ipc_table(t_info *info, t_list *list, int i)
{
	t_process_info	*p_info;


	p_info = (t_process_info *)ft_calloc(1, sizeof(t_process_info));
	p_info->section = info->process_cnt - i;
	p_info->cmd = lst_to_arr(list);
	convert_to_cmd_full_path(info, p_info);
	// int a = 0;
	// while (p_info->cmd[a])
	// 	printf("[%d]:%s\n", p_info->section, p_info->cmd[a++]);
	if (p_info->section + 1 != info->process_cnt && \
					pipe(info->pipefd[p_info->section]) < 0)
		exit (1);// exit(free_all_info(info, true, 1));
	info->pid[p_info->section] = fork();
	if (info->pid[p_info->section] == -1)
		exit (1);// exit(free_all_info(info, true, 1));
	else if (info->pid[p_info->section] == 0)
		child_exe(info, p_info);
	else
	{
		if (p_info->section != 0)
		{
			safe_func(close(info->pipefd[p_info->section - 1][0]), info);
			safe_func(close(info->pipefd[p_info->section - 1][1]), info);
		}
	}
}

static void crawl_ast(t_ms_ast *ms_ast, t_info *info, int i)
{
	if (ms_ast->left_node && ms_ast->type == PIPE)
		crawl_ast(ms_ast->left_node, info, ++i);
	if (ms_ast->right_node && ms_ast->right_node->cmd_info_list)
	{
		ipc_table(info, ms_ast->right_node->cmd_info_list, i);
	}
	if (ms_ast->cmd_info_list)
		ipc_table(info, ms_ast->cmd_info_list, info->process_cnt);
	return ;
}

int	executor_test(t_ms_ast *ms_ast, t_envlist *envlist, char **envp)
{
	t_info	*info;
	t_process_info *p_info;
	t_list	*list;
	int		wstatus;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	info->envp = envp;
	info->envlist = envlist;
	info->ms_ast = ms_ast;
	info->process_cnt = 4;
	info->pid = (pid_t *)malloc(sizeof(pid_t) * info->process_cnt);
	info->pipefd = (int **)ft_calloc(info->process_cnt, sizeof(int *));
	int i = 0;
	while (i < info->process_cnt)
		info->pipefd[i++] = (int *)ft_calloc(2, sizeof(int));
	crawl_ast(ms_ast, info, 0);
	i = 0;
	while (i < info->process_cnt)
	{
		// printf("%d\n", info->pid[i]);
		safe_func(waitpid(info->pid[i], &wstatus, WUNTRACED), info);
		i++;
	}
	return (WEXITSTATUS(wstatus));
}

t_ms_ast	*lexer_and_parser(char *str, t_info *info)
{
	char		**tokenized_line;
	char		***splited_pipe;
	t_ms_ast	*ms_ast;

	tokenized_line = tokenize_main(str);
	if (!tokenized_line)
		;
	// print_tokenized_line(tokenized_line);
	splited_pipe = split_by_pipe(tokenized_line);
	if (!splited_pipe)
		;
	// print_sbp(splited_pipe);
	ms_ast = make_ast(splited_pipe);
	if (!ms_ast)
		;
	// printf("\n↓print_ast\n\n");
	// print_ast(ms_ast);
	return (ms_ast);
}


// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q lexer_and_parser");
// }

int	main(int argc, char **argv, char **envp)
{
	// char 		str[] = "<cat file2|grep \"he' ohayo-'llo\"||||wc -l  ><<< > file2 >";
	// char		str[] = ">>ls |<<| cat file2 >> file3|| grep -i  \"first\" | wc -l >> outfile";
	// char		str[] = "cat ipc_executor.c | head -n20 | tail -n10";
	// char	str[] = "cat lexer_and_parser.h | wd | head -n 20 | cat Makefile";
	// char 	str[] = "cat | cat | cat | ls";
	// char		str[] = "export TEST=\"hello\"";
	// char 		str[] = "";
	char 		**tokenized_line;
	t_ms_ast	*ms_ast;
	size_t		tl_len;
	t_envlist	*envlist;

	//引数使用
	argc = 0;
	argv = NULL;

	// printf("source_line:[%s]\n", str);
	t_info *info;
	ms_ast = lexer_and_parser(str, info);
	if (!ms_ast)
		return (0);
	// system("leaks -q lexer_and_parser");
	envlist = create_envlist(envp);
	int	exit_status;
	exit_status = executor_test(ms_ast, envlist, envp);
	printf("\n\n[$?=%d]\n", exit_status);
	free_ast(ms_ast);
	// system("leaks -q lexer_and_parser");
	return (0);
}

//パイプが最初or最後にあればsyntax_error
//クォーとが偶数子でなかった場合
//パイプが二つ続く場合
//リダイレクト関係
// < |
