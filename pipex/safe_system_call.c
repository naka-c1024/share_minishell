/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_system_call.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:16:39 by kahirose          #+#    #+#             */
/*   Updated: 2022/02/28 12:07:55 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	safe_func(int res, t_info *info)
{
	if (res == -1)
	{
		free_all_info(info, true, 1);
		exit(1);
	}
	return (res);
}
