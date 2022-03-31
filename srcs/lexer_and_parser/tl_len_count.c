/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tl_len_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 01:09:22 by kahirose          #+#    #+#             */
/*   Updated: 2022/04/01 01:13:06 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "lexer_and_parser.h"

size_t  tokens_count(char *str)
{
    printf("%s\n", str);
}

int main(void)
{
    char str[] = "cat file2 | grep \"hello\" | wc -l >> outfile"
    int  tl_len = 0;

    tl_len = tokens_count(str);
    return (0);
}