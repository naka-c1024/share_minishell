/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:02:46 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 05:23:27 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

static int	token_counter(char **cmd_line_start)
{
	int	count;

	count = 0;
	while (cmd_line_start[count] && cmd_line_start[count][0] != '|')
		count++;
	return (count);
}

static void	result_init(char **tokenized_line, \
						char ****result, size_t *proc_cnt)
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
	*result = (char ***)ft_x_calloc(sizeof(char **), counter * 2);
	*proc_cnt = counter;
}

static int	make_single_proc_line(char **tokenized_line, \
								int tl_i, char ***result, int res_i)
{
	size_t	token_cnt;
	int		res_j;

	res_j = 0;
	token_cnt = token_counter(&(tokenized_line[tl_i]));
	result[res_i] = (char **)ft_x_calloc(token_cnt + 1, sizeof(char *));
	while (tokenized_line[tl_i] && tokenized_line[tl_i][0] != '|')
	{
		result[res_i][res_j] = ft_x_strdup(tokenized_line[tl_i]);
		tl_i++;
		res_j++;
	}
	result[res_i][res_j] = NULL;
	return (tl_i);
}

static int	make_pipe_line(char **tokenized_line, \
						int tl_i, char ***result, int res_i)
{
	result[res_i] = (char **)ft_x_calloc(sizeof(char *), 2);
	result[res_i][0] = ft_x_strdup(tokenized_line[tl_i++]);
	result[res_i][1] = NULL;
	return (tl_i);
}

char	***split_by_pipe(char **tokenized_line, size_t *process_cnt)
{
	char	***result;
	int		tl_i;
	int		res_i;
	int		res_j;

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
	free_two_d_arr(tokenized_line);
	return (result);
}
