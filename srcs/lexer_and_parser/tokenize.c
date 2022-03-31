#include "lexer_and_parser.h"

typedef	struct s_lexer_info
{
	char	**tokenized_line;
	char	*line;
	int		*line_index;
	int		*line_start_index;
	int		*tl_index;
}	t_lexer_info;

static int	tl_len_count(char *line)
{
	int	tl_len;

	tl_len = 30;
	return (tl_len);
}

static bool	is_valid_pre_string(t_lexer_info *l_info)
{
	if (*(l_info->line_index) == 0 || \
		l_info->line[(*(l_info->line_index)) - 1] == '|' || \
			l_info->line[(*(l_info->line_index)) - 1] == ' ' || \
				l_info->line[(*(l_info->line_index)) - 1] == '"' || \
					l_info->line[(*(l_info->line_index)) - 1] == '\'' || \
						l_info->line[(*(l_info->line_index)) - 1] == '>')
		return (false);
	return (true);
}

static void	last_word_taker(t_lexer_info *l_info)
{
	if (is_valid_pre_string(l_info))
	{
		l_info->tokenized_line[(*(l_info->tl_index))++] = \
			ft_substr(l_info->line, *(l_info->line_start_index), \
				*(l_info->line_index) - *(l_info->line_start_index));
		if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		{
			//free処理
			;
		}
		return ;
	}
	printf("\n\n!!!!\n    last_word_is_separator\n\n");
}

static void	quote_separator(t_lexer_info *l_info)
{
	char	target;

	target = l_info->line[*(l_info->line_index)];
	(*(l_info->line_index))++;
	while (l_info->line[*(l_info->line_index)] && \
			l_info->line[*(l_info->line_index)] != target)
		(*(l_info->line_index))++;
	if (l_info->line[*(l_info->line_index)] != target)
	{
		printf("syntax error\n");
		exit(0); //free処理
	}
	(*(l_info->line_index))++;
	l_info->tokenized_line[(*(l_info->tl_index))++] = \
		ft_substr(l_info->line, *(l_info->line_start_index), \
			*(l_info->line_index) - *(l_info->line_start_index));
	if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		; //free処理
	*(l_info->line_start_index) = *(l_info->line_index);
}

static void	pipe_separator(t_lexer_info *l_info)
{
	if (is_valid_pre_string(l_info))
	{
		l_info->tokenized_line[(*(l_info->tl_index))++] = \
			ft_substr(l_info->line, *(l_info->line_start_index), \
				*(l_info->line_index) - *(l_info->line_start_index));
		if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
			;//free処理
	}
	else if (*(l_info->line_index) == 0)
		exit (printf("syntax error\n")); //free処理も
	l_info->tokenized_line[(*(l_info->tl_index))++] = \
		ft_substr(l_info->line, (*(l_info->line_index))++, 1);
	if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		; //free処理
	*(l_info->line_start_index) = *(l_info->line_index);
}

static void	single_redirect_separator(t_lexer_info *l_info)
{
	if (is_valid_pre_string(l_info))
	{
		l_info->tokenized_line[(*(l_info->tl_index))++] = \
			ft_substr(l_info->line, *(l_info->line_start_index), \
				*(l_info->line_index) - *(l_info->line_start_index));
		if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
			;//free処理
	}
	l_info->tokenized_line[(*(l_info->tl_index))++] = \
		ft_substr(l_info->line, (*(l_info->line_index))++, 1);
	if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		; //free処理
	*(l_info->line_start_index) = *(l_info->line_index);
}

static void	space_separator(t_lexer_info *l_info)
{
	if (is_valid_pre_string(l_info)) //初っ端からスペースだった場合に、空文字列が作られるのを防ぐ
	{
		l_info->tokenized_line[(*(l_info->tl_index))++] = \
		ft_substr(l_info->line, *(l_info->line_start_index), \
		*(l_info->line_index) - *(l_info->line_start_index));
		if (!(l_info->tokenized_line[(*(l_info->tl_index)) - 1]))
		{
			//free処理
			;
		}
	}
	while (l_info->line[*(l_info->line_index)] == ' ')
		(*(l_info->line_index))++;
	*(l_info->line_start_index) = *(l_info->line_index);
}

static	bool is_quote(t_lexer_info *l_info)
{
	if (l_info->line[*(l_info->line_index)] == '\'' || \
		l_info->line[*(l_info->line_index)] == '"' )
			return (true);
	return (false);
}

static	bool is_single_redirect(t_lexer_info *l_info)
{
	if (l_info->line[*(l_info->line_index)] == '>' || \
		l_info->line[*(l_info->line_index)] == '<')
				return (true);
	return (false);
}

static char **tokenize(t_lexer_info *l_info)
{
	char	**tokenized_line;
	int		tl_len;

	tl_len = tl_len_count(l_info->line);
	tokenized_line = (char **)malloc(sizeof(char *) * tl_len);
	l_info->tokenized_line = tokenized_line;
	while (l_info->line[*(l_info->line_index)])
	{
		if (l_info->line[*(l_info->line_index)] == ' ')
			space_separator(l_info);
		else if (l_info->line[*(l_info->line_index)] == '|')
			pipe_separator(l_info);
		else if (is_quote(l_info))
				quote_separator(l_info);
		else if (is_single_redirect(l_info))
			single_redirect_separator(l_info);
		else
			(*(l_info->line_index))++;
	}
	last_word_taker(l_info);
	l_info->tokenized_line[*(l_info->tl_index)] = NULL;
	return (l_info->tokenized_line);
}

char	**tokenize_main(char *line)
{
	t_lexer_info	*l_info;
	int				line_index;
	int				line_start_index;
	char			**tokenized_line;
	int				tl_index;

	line_index = 0;
	line_start_index = 0;
	tl_index = 0;
	// tokenized_line = (char **)malloc(sizeof(char *) * 20);//wc関数
	l_info = (t_lexer_info *)malloc(sizeof(t_lexer_info));
	l_info->line = line;
	l_info->line_index = &line_index;
	l_info->line_start_index = &line_start_index;
	l_info->tl_index = &tl_index;
	// printf("%p\n", (l_info->line_index));
	// printf("292:%s\n", l_info->line);
	tokenized_line = tokenize(l_info);
	return (tokenized_line);
}

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
