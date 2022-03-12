/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:33:01 by ynakashi          #+#    #+#             */
/*   Updated: 2021/11/06 16:44:38 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	read_sign(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

static bool	is_space(char c)
{
	if ((c == ' ') || (c == '\t') || (c == '\n')
		|| (c == '\v') || (c == '\r') || (c == '\f'))
		return (true);
	else
		return (false);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	long	ans;

	ans = 0;
	i = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = read_sign(str[i++]);
	while (ft_isdigit(str[i]))
	{
		if ((ans * 10 + (str[i] - '0')) / 10 != ans)
		{
			if (sign == -1)
				return ((int)LONG_MIN);
			else
				return ((int)LONG_MAX);
		}
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return ((int)(ans * sign));
}
// not NULL guard
// gcc -g -fsanitize=undefined ft_atoi.c libft.a && ./a.out
// 未定義動作は許されている
// Your functions should not quit unexpectedly
// (segmentation fault, bus error, double free, etc)
// apart from undefined behaviors.(apart from: ~とは別に)
// man -> It is equivalent to : (int)strtol(str, (char **)NULL, 10);
/*
#include <libc.h>
#include <limits.h>
void sub_func(char *str, int f(char *), int ft_f(char *))
{
	printf("%s: %d, %d\n", str, f(str), ft_f(str));
}

int main(void)
{
	printf("TEST\n");
	sub_func("9999999999999999999999999999999999999999", atoi, ft_atoi);
	sub_func("-999999999999999999999999999999999999999", atoi, ft_atoi);
	sub_func("--100", atoi, ft_atoi);
	sub_func("\n+\t3", atoi, ft_atoi);
	sub_func("100ab100", atoi, ft_atoi);
	sub_func("1.1", atoi, ft_atoi);
	sub_func("  ---+--+1234ab567", atoi, ft_atoi);
	sub_func("\t\n\v\f\r 42", atoi, ft_atoi);
	sub_func("0042", atoi, ft_atoi);
	sub_func(" +--123-", atoi, ft_atoi);
	sub_func("\0", atoi, ft_atoi);
	sub_func("", atoi, ft_atoi);
	printf("---------------\n");

	printf("INT_MAX: %d\n", INT_MAX);
	sub_func("2147483646", atoi, ft_atoi);
	sub_func("2147483647", atoi, ft_atoi);
	sub_func("2147483648", atoi, ft_atoi);
	printf("---------------\n");

	printf("INT_MIN: %d\n", INT_MIN);
	sub_func("-2147483647", atoi, ft_atoi);
	sub_func("-2147483648", atoi, ft_atoi);
	sub_func("-2147483649", atoi, ft_atoi);
	printf("---------------\n");

	printf("UINT_MAX: %u\n", UINT_MAX);
	sub_func("4294967294", atoi, ft_atoi); // strtolではオーバーフローしてない
	sub_func("4294967295", atoi, ft_atoi);
	sub_func("4294967296", atoi, ft_atoi);
	printf("---------------\n");

	printf("LONG_MAX: %ld\n", LONG_MAX);
	printf("---------------\n");
	sub_func("9223372036854775806", atoi, ft_atoi); // strtolではオーバーフローしてない
	sub_func("9223372036854775807", atoi, ft_atoi);
	sub_func("9223372036854775808", atoi, ft_atoi);
	printf("---------------\n");

	printf("LONG_MIN: %ld\n", LONG_MIN);
	printf("---------------\n");
	sub_func("-9223372036854775807", atoi, ft_atoi);
	sub_func("-9223372036854775808", atoi, ft_atoi);
	sub_func("-9223372036854775809", atoi, ft_atoi);
	printf("---------------\n");

	printf("ULONG_MAX: %lu\n", ULONG_MAX);
	printf("---------------\n");
	sub_func("18446744073709551614", atoi, ft_atoi);
	sub_func("18446744073709551615", atoi, ft_atoi);
	sub_func("18446744073709551616", atoi, ft_atoi);

	return (0);
}
 */
// オーバーフロー対策その2
// これは(ans * 10 + (str[i] - '0')) > LONG_MAXを式変形したもの
		// if (sign == 1 && ans > (LONG_MAX - (str[i] - '0')) / 10)
		// 	return ((int)LONG_MAX);
		// if (sign == -1 && (-1 * ans) < (LONG_MIN + (str[i] - '0')) / 10)
		// 	return ((int)LONG_MIN);
/*
// マクロの確認
#include <libc.h>
#include <limits.h>
int	main(void)
{
	printf("%d\n", INT_MAX);
	printf("%d\n", INT_MIN);
	printf("%u\n", UINT_MAX);

	printf("%ld\n", LONG_MAX);
	printf("%ld\n", LONG_MIN);
	printf("%lu\n", ULONG_MAX);

	printf("%lld\n", LONG_LONG_MAX);
	printf("%lld\n", LONG_LONG_MIN);
	printf("%llu\n", ULONG_LONG_MAX);

	return (0);
}
 */
/*
// キャストとは
#include <libc.h>
#include <limits.h>
// gccを使う
int	main(void)
{
	printf("%d\n", (int)INT_MAX + 1);
	// printf("%d\n", (int)INT_MIN - 1);
	printf("%d\n", (int)LONG_MAX);
	printf("%d\n", (int)LONG_MIN);
	printf("%d\n", (int)4294967294);
}
 */
/*
// 割り算の切り捨て
#include <libc.h>
int	main(void)
{
	printf("%d\n", 42 / 10);
}
 */
