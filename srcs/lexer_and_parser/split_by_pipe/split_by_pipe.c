/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:02:46 by kahirose          #+#    #+#             */
/*   Updated: 2022/05/16 07:17:15 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

static int	token_counter(char **cmd_line_start)
{
	int	count;

	count = 0;
	while (cmd_line_start[count] && cmd_line_start[count][0] != '|')
		count++;
	// printf("count:%d\n", count);
	return (count);
}

void	free_2d_line(char **two_d_line)
{
	size_t	idx;

	idx = 0;
	if (two_d_line)
	{
		while (two_d_line[idx])
			free(two_d_line[idx++]);
		free(two_d_line[idx]);
		//最後free(two_d_line[idx]);しないとだめだろ
	}
	free(two_d_line);
}

void	free_3d_line(char ***three_d_line)
{
	size_t	fir;
	size_t	sec;

	fir = 0;
	if (three_d_line)
	{
		while (three_d_line[fir])
		{
			sec = 0;
			while (three_d_line[fir][sec])
				free(three_d_line[fir][sec++]);
			free(three_d_line[fir++]);
		}
	}
	free (three_d_line);
}

void	error_occuration_at_sbp(char **tokenized_line, char ***result)
{
	free_2d_line(tokenized_line);
	free_3d_line(result);
	printf("error\n");
}

static void	result_init(char **tokenized_line, char ****result, size_t *proc_cnt)
{
	int		idx;
	int		counter;

	idx = 0;
	counter = 1;
	while (tokenized_line[idx])
	{
		if (tokenized_line[idx][0] == '|')
			counter++;
		idx++;
	}
	*result = (char ***)ft_calloc(sizeof(char **), counter * 2);
	if (!(*result))
		error_occuration_at_sbp(tokenized_line, *result);
	*proc_cnt = counter;
}

static int	make_single_proc_line(char **tokenized_line, \
								int tl_i, char ***result, int res_i)
{
	size_t	token_cnt;
	int		res_j;

	res_j = 0;
	token_cnt = token_counter(&(tokenized_line[tl_i]));
	result[res_i] = (char **)ft_calloc(token_cnt + 1, sizeof(char *));
	if (!result[res_i])
		error_occuration_at_sbp(tokenized_line, result);
	while (tokenized_line[tl_i] && tokenized_line[tl_i][0] != '|')
	{
		result[res_i][res_j] = ft_strdup(tokenized_line[tl_i]);
		if (!result[res_i][res_j])
			error_occuration_at_sbp(tokenized_line, result);
		tl_i++;
		res_j++;
	}
	result[res_i][res_j] = NULL;
	return (tl_i);
}

static int	make_pipe_line(char **tokenized_line, \
						int tl_i, char ***result, int res_i)
{
	result[res_i] = (char **)ft_calloc(sizeof(char *), 2);
	if (!result[res_i])
		error_occuration_at_sbp(tokenized_line, result);
	result[res_i][0] = ft_strdup(tokenized_line[tl_i++]);//ft_strdup("|")のほうが可読性は高い気がする
	if (!result[res_i][0])
		error_occuration_at_sbp(tokenized_line, result);
	result[res_i][1] = NULL;
	return (tl_i);
}

// static bool	serch_heredoc_symbol(char **token)
// {
// 	int	idx;

// 	idx = 0;
// 	while (token[idx])
// 	{
// 		if (!ft_strncmp(token[idx++], "<<", 2))
// 			return (true);
// 	}
// 	return (false);
// }

// static ssize_t	continuous_heredoc_len(char ***result)
// {
// 	size_t	fir_idx;

// 	fir_idx = 0;
// 	while (result[fir_idx])
// 	{
// 		if (result[fir_idx][0][0] != '|' && \
// 			serch_heredoc_symbol(result[fir_idx]) == false)
// 			break;
// 		fir_idx++;
// 	}
// 	return (fir_idx);
// }

// static void	front_shift_process_node(char ***result, size_t fir_idx, size_t limit)
// {
// 	char	**tmp;

// 	printf("fspn:running\n");
// 	while (fir_idx != limit)
// 	{
// 		tmp = result[fir_idx];
// 		result[fir_idx] = result[fir_idx - 2];
// 		result[fir_idx - 2] = tmp;
// 		fir_idx -= 2;
// 	}
// }

// static void	sort_by_heredoc(char ***result)
// {
// 	size_t	fir_idx;
// 	size_t	sec_idx;
// 	size_t	process_idx;
// 	ssize_t	heredoc_last;
// 	char	**tmp;

// 	process_idx = 0;
// 	heredoc_last = continuous_heredoc_len(result);
// 	printf("aiu:%zu\n", heredoc_last);
// 	fir_idx = heredoc_last;
// 	while (result[fir_idx] && result[fir_idx + 1])
// 	{
// 		fir_idx = heredoc_last;
// 		while (result[fir_idx])
// 		{
// 			if (result[fir_idx][0][0] != '|' && \
// 				serch_heredoc_symbol(result[fir_idx]))
// 			{
// 				front_shift_process_node(result, fir_idx, heredoc_last);
// 				if (result[(heredoc_last++) + 1][0] != NULL)
// 					heredoc_last ++;
// 				break;
// 			}
// 			fir_idx++;
// 		}
// 	}
// }

char	***split_by_pipe(char **tokenized_line, size_t *process_cnt)
{
	char	***result;
	int		tl_i;
	int		res_i;
	int		res_j;
	// int		token_cnt;

	result_init(tokenized_line, &result, process_cnt);
	tl_i = 0;
	res_i = 0;
	while (tokenized_line[tl_i])
	{
		res_j = 0;
		if (tokenized_line[tl_i][0] != '|')
			tl_i = \
				make_single_proc_line(tokenized_line, tl_i, result, res_i);
		else
			tl_i = make_pipe_line(tokenized_line, tl_i, result, res_i);
		res_i++;
	}
	result[res_i] = NULL;
	free_2d_line(tokenized_line);
	return (result);
}

// #include <string.h>
// int main(void)
// {
// 	char	**splited_by_pipe;
// 	size_t	process_cnt;
// 	char	***result;

// 	splited_by_pipe = (char **)calloc(17, sizeof(char *));
// 	int	i = 0;
// 	while (i < 16)
// 	{
// 		splited_by_pipe[i++] = (char *)calloc(10, sizeof(char));
// 	}

// 	splited_by_pipe[0] = "cat";
// 	splited_by_pipe[1] = "<";
// 	splited_by_pipe[2] = "file1";
// 	splited_by_pipe[3] = "|";
// 	splited_by_pipe[4] = "cat";
// 	splited_by_pipe[5] = "<<";
// 	splited_by_pipe[6] = "file2";
// 	splited_by_pipe[7] = "|";
// 	splited_by_pipe[8] = "cat";
// 	splited_by_pipe[9] = "<<";
// 	splited_by_pipe[10] = "file3";
// 	splited_by_pipe[11] = "|";
// 	splited_by_pipe[12] = "cat";
// 	splited_by_pipe[13] = "<<";
// 	splited_by_pipe[14] = "file4";
// 	splited_by_pipe[15] = NULL;
// 	i = 0;
// 	result = split_by_pipe(splited_by_pipe, &process_cnt);
// 	print_sbp(result);
// 	return (0);
// }
