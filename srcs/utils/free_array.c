/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 04:50:56 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/07 04:59:51 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_two_d_arr(char **two_d_line)
{
	size_t	idx;

	idx = 0;
	if (two_d_line)
	{
		while (two_d_line[idx])
			free(two_d_line[idx++]);
		free(two_d_line[idx]);
	}
	free(two_d_line);
}

void	free_three_d_arr(char ***three_d_line)
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
