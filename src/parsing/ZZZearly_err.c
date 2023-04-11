

// int	opening_pipe_err(char *input)
// {
// 	if (input[0] == '|')
// 		return (1);
// 	return (0);
// }

// int	newline_err(char *input)
// {
// 	if (input[ft_strlen(input) - 1] == '<'
// 		|| input[ft_strlen(input) - 1] == '>' //)
// 		|| input[ft_strlen(input) - 1] == '|') // not really bash - last PIPE is waiting for input) 
// 		return (1);
// 	return (0);
// }

/*
early error check:

0. getting rid of white spaces at the beginning/end of string
1. quotes must be closed -> minishell: unsupported open quotes

2. first char may not be a pipe -> minishell: syntax error
near unexpected token `|'
3. last char may not be an operator (since it' s not 100% bash,
it also doesn't support PIPE as a last char)

remaining syntax check is performed after tokenization, makes it easier
*/

// int	early_err(t_data *data)
// {
// 	char *input = data->input;
// 	if (unsupported_quotes_err(input) == -1)
// 		return (printf("minishell: unsupported open quotes\n"), -1);
	// manipulate_input(&input);
	// if (input[0]) //only empty spaces
	// 	return (1);
	// if (opening_pipe_err(input))
	// 	return (printf
	// 		("minishell: syntax error near unexpected token `|'\n"));
	// if (newline_err(input))
	// 	return (printf
	// 		("minishell: syntax error near unexpected token `newline'\n"));
	// if (unsupported_pipe_err(input))
	// 	return (printf("minishell: unsupported double pipe\n"));
	// if (unsupported_redir_err(input, '>')|| unsupported_redir_err(input, '<'))
	// 	return (printf("minishell: only < << > >> supported\n"));
	// if (unsupported_char_err(input))
	// 	return (printf
	// 		("minishell: unsupported special chars: & ; \\\n"));
// 	return (0);
// }

//MAYBE ADD CHECK FOR EMTY STRING

// add cases like >< or <| >|