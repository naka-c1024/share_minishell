/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_system_call.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahirose <kahirose@studnt.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:10:16 by kahirose          #+#    #+#             */
/*   Updated: 2022/06/06 20:11:52 by kahirose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_func(int result_status)
{
	if (result_status == -1)
	{
		perror("minishell");
		exit(1);
	}
	return (result_status);
}

int	safe_func_with_file(int result_status, char *file_name)
{
	if (result_status == -1)
	{
		safe_func(write(1, "minishell: ", 11));
		perror(file_name);
		exit (1);
	}
	return (result_status);
}
//systemcall lineup -> write dup close access pipe waitpid fork
//perror exit は戻り値なし openは個別で対応

//sb_set_in_file関数77行目は、accessで開けると判断できたものなので完全にopenが他の原因で失敗した
//これは、exitしなくてよいのか問題
//それとput_file_err_msgではproc_infoを持っていっているがフリーしなくても良いのか問題

//int main(void)
//{
	//char	str[10] = "hello\n";
	//char	*line;

	//line = readline(">");
	//free(line);
	//free(line);
	//return (0);
//}
//上記のメイン関数の結果よりreadlineで取得した文字列はmallocされている

//int main(void)
//{
	//char	*line;
	//int		result;

	////line = malloc(sizeof(void *) * LONG_MAX);
	//while (1)
	//{
		//result = dup(1);
		//printf("%d\n", result);
		//if (result == -1)
		//{
			//perror("minishell");
			//exit(1);
		//}
	//}
	//return (0);
//}
