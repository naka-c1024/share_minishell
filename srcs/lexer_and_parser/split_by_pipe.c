/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:02:46 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/04 14:06:14 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_and_parser.h"

static int	token_counter(char **cmd_line_start)
{
	int	count;

	count = 0;
	while (cmd_line_start[count] && cmd_line_start[count][0] != '|')
		count++;
	printf("count:%d\n", count);
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
			if (three_d_line[fir])
			{
				while (three_d_line[fir][sec])
					free(three_d_line[fir][sec++]);
			}
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

static void	result_init(char **tokenized_line, char ****result)
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
	result[res_i][0] = ft_strdup(tokenized_line[tl_i++]);
	if (!result[res_i][0])
		error_occuration_at_sbp(tokenized_line, result);
	result[res_i][1] = NULL;
	return (tl_i);
}

char	***split_by_pipe(char **tokenized_line)
{
	char	***result;
	int		tl_i;
	int		res_i;
	int		res_j;
	int		token_cnt;

	result_init(tokenized_line, &result);
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
