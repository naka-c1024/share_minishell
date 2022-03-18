/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynakashi <ynakashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 17:57:12 by ynakashi          #+#    #+#             */
/*   Updated: 2021/10/30 18:10:02 by ynakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}
/*
void	ft_putchar_fd(char c, int fd)
{
	char	head;
	char	tail;
	char	mask1;
	char	mask2;

	 // asciiの範囲内
	if ((unsigned char)c <= 0x7F)
	{
		write(fd, &c, sizeof(char));
	}
	 // 0x80以上は2バイト文字の領域
	else
	{
		mask1 = 0b00111111;
		mask2 = 0b11000000;

		 // 2バイトの前
		 // cの上位2ビット分を取り出して、6ビット右にシフトして、先頭に11をつける
		head = (((unsigned char)c & mask2) >> 6) | mask2;
		 // 2バイトの後ろ
		 // cの下位6ビット分を取り出して、先頭に10をつける
		tail = ((unsigned char)c & mask1) | 0b10000000;

		write(fd, &head, 1);
		write(fd, &tail, 1);
	}
}
 */
/*
#include <libc.h>
int	main(void)
{
	// putc('a', stdout);
	// putc('\n', stdout);
	ft_putchar_fd('a', STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);

	//1byte 'a' = 01100001(97)
	//2byte '½' = 11000010(194):10111101(189)
	//3byte 'あ' = 11100011(227):10000001(129):10000010(130)
	//4byte '𐆐' = 11110000(240):10010000(144):10000110(134):10010000(144) //error

	// putc(194, stdout);
	// putc(189, stdout);
	// putc('\n', stdout);

	// ft_putchar_fd((char)194, STDOUT_FILENO);
	// ft_putchar_fd((char)189, STDOUT_FILENO);
	// ft_putchar_fd('\n', STDOUT_FILENO);

	// putc(227, stdout);
	// putc(129, stdout);
	// putc(130, stdout);
	// putc('\n', stdout);

// error
	// putc('240', stdout);
	// putc('144', stdout);
	// putc('134', stdout);
	// putc('144', stdout);
	// putc('\n', stdout);

	return (0);
}
 */
