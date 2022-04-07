// int	main(void)
// {
// 	char 		*str = (char *)malloc(sizeof(char) * 100);
// 	str = "  cat file2|grep|'hel\"l\"o''aiueo'  | ||||\"wc -l    aal   |  |||";//スペースの後ろにセパレータが来るとまずい
// 	t_ms_ast	*ms_ast;
// 	char 		**tokenized_line;

// 	printf("%s\n", str);
// 	tokenized_line = tokenize_main(str);

// 	int i = 0;
// 	printf("exepected:[  cat file2|grep|'hel\"l\"o\'||||\"w'c -l    aal   |   |||]\n");
// 	printf("\n\nresult   :");
// 	while (tokenized_line[i])
// 	{
// 		if (!tokenized_line[i][0])
// 		{
// 			printf("\x1b[35m[null]\x1b[39m");
// 			i++;
// 		}
// 		else
// 			printf("[%s]", tokenized_line[i++]);
// 	}
// 	printf("\n");
// 	// ms_ast = lexer_and_parser(str);
// 	return(0);
// }
