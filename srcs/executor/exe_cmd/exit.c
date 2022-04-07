/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 20:01:41 by ynakashi          #+#    #+#             */
/*   Updated: 2022/04/07 17:32:53 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_cmd.h"

static int	read_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

static bool	check_arg_value(char *str)
{
	size_t		i;
	size_t		len;
	int			sign;
	long long	abs_val;

	abs_val = 0;
	i = 0;
	len = ft_strlen(str);
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		sign = read_sign(str[i++]);
	while (ft_isdigit(str[i]))
	{
		if (sign == 1 && abs_val > (LONG_MAX - (str[i] - '0')) / 10)
			return (false);
		if (sign == -1 && (-1 * abs_val) < (LONG_MIN + (str[i] - '0')) / 10)
			return (false);
		abs_val *= 10;
		abs_val += str[i] - '0';
		i++;
	}
	if (len != i)
		return (false);
	return (true);
}

static bool	is_space(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\n')
		|| (c == '\v') || (c == '\r') || (c == '\f'))
		return (true);
	else
		return (false);
}

static long	my_atol(const char *str)
{
	size_t		i;
	int			sign;
	long long	ans;

	ans = 0;
	i = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = read_sign(str[i++]);
	while (ft_isdigit(str[i]))
	{
		if (sign == 1 && ans > (LONG_MAX - (str[i] - '0')) / 10)
			return (LONG_MAX);
		if (sign == -1 && (-1 * ans) < (LONG_MIN + (str[i] - '0')) / 10)
			return (LONG_MIN);
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return (ans * sign);
}

int	my_exit(char **split_ln)
{
	size_t	cnt;
	long	arg_value;

	cnt = 0;
	while (split_ln[cnt] != NULL && cnt < 3)
		cnt++;
	if (cnt == 1)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS); // 後で修正
	}
	else if (check_arg_value(split_ln[1]) == false) // オーバーフローと文字を見る
	{
		numeric_argument_required(split_ln[1]);
		exit(255);
	}
	if (cnt > 2)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putendl_fd("my_shell: exit: too many arguments", STDERR_FILENO);
		return (1); // ここだけexitしない
	}
	arg_value = my_atol(split_ln[1]);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(arg_value);
}
