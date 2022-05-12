/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 13:54:39 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/23 20:19:00 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_valid_start_file(t_info info)
{
	if (access(info.argv[1], R_OK) == 0)
		return (true);
	return (false);
}
