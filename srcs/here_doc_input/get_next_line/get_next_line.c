/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:07:08 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/23 15:28:50 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*make_result(char **all)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = gnl_strlen(*all, 1);
	i = 0;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (**all != '\0' && **all != '\n')
	{
		result[i] = **all;
		*all = *all + 1;
		i++;
	}
	if (**all == '\n')
	{
		*all = *all + 1;
		result[i++] = '\n';
	}
	result[i] = '\0';
	return (result);
}

static char	*tail_trim(char *all, char **save)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len;
	char	*keep_all;

	keep_all = all;
	j = 0;
	result = make_result(&all);
	if (result == NULL)
		return (error_clean(keep_all, NULL));
	len = gnl_strlen(all, 0);
	*save = (char *)malloc(sizeof(char) * (len + 1));
	if (*save == NULL)
		return (error_clean(keep_all, result));
	i = 0;
	while (all[i] != '\0')
	{
		(*save)[i] = all[i];
		i++;
	}
	(*save)[i] = '\0';
	free(keep_all);
	return (result);
}

static int	eol_sensor(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*take_next_line(char *save, int fd)
{
	char		*buf;
	char		*new;
	ssize_t		rd;

	rd = 1;
	if (eol_sensor(save) == 1)
		return (save);
	new = save;
	while (rd != 0)
	{
		buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
		if (buf == NULL)
			return (error_clean(new, NULL));
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1 || (rd == 0 && gnl_strlen(new, 0) == 0))
			return (error_clean(new, buf));
		buf[rd] = '\0';
		new = gnl_strjoin(new, buf);
		if (new == NULL)
			return (NULL);
		if (eol_sensor(new) == 1)
			return (new);
	}
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save == NULL)
	{
		save = (char *)malloc(sizeof(char) * 1);
		if (save == NULL)
			return (NULL);
		*save = '\0';
	}
	result = take_next_line(save, fd);
	if (result == NULL)
	{
		save = NULL;
		return (NULL);
	}
	result = tail_trim(result, &save);
	if (result == NULL)
		save = NULL;
	return (result);
}
