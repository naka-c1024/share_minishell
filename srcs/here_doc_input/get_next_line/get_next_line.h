/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:58:50 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/18 15:45:02 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256

# endif

size_t	gnl_strlen(const char *str, int mode);
char	*ft_strcat(char *dest, char *src);
char	*gnl_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
void	*error_clean(char *s1, char *s2);

#endif
