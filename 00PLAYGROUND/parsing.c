
#include "../../includes/minishell.h"

// int save_token_or_return_start(int *i, int token_start, t_data *data);
// int	tokenizer(t_data *data);
// int		isseparator(char *s, int i);
// int	check_quotation(int current_quotation, char *s, int i);


// typedef struct s_token
// {
// 	char			*str;
// 	int				type;
// 	struct s_token	*next;
// }	t_token;


// enum e_q_status {
// 	NONE_OR_CLOSED,
// 	SINGLE_Q,
// 	DOUBLE_Q
// };

// Without quotes, bash tries to evaluate all special characters
// Single quotes (') prevent all evaluation
// Double quotes (") prevent most evaluation,
// but notably not the evaluation of variables


// int	isseparator(char *s, int i)
// {
// 	if (((s[i] > 8 && s[i] < 14) || s[i] == 32))
// 		return (SPACE);
// 	else if (s[i] == '|')
// 		return (PIPE);
// 	else if (s[i] == '\'')
// 		return (S_Q);
// 	else if (s[i] == '\"')
// 		return (D_Q);
// 	else if (s[i] == '<')
// 		return (IN);
// 	else if (s[i] == '>')
// 		return (OUT);
// 	else if (s[i] == '<' && s[i + 1] == '<') // 
// 		return (HERED);
// 	else if (s[i] == '>' && s[i + 1] == '>')
// 		return (APPEND);
// 	else if (s[i] == '\0')
// 	 	return (END);
// 	else
// 		return (0);
// }

// int	check_quotation(int current_quotation, char *s, int i)
// {
// 	if (s[i] == '\'' && current_quotation == NONE_OR_CLOSED)
// 		current_quotation = SINGLE_Q; //retrn 1
// 	else if (s[i] == '\"' && current_quotation == NONE_OR_CLOSED)
// 		current_quotation = DOUBLE_Q; // return 2
// 	else if (s[i] == '\'' && current_quotation == SINGLE_Q)
// 		current_quotation = NONE_OR_CLOSED; //return 0
// 	else if (s[i] == '\"' && current_quotation == DOUBLE_Q)
// 		current_quotation = NONE_OR_CLOSED; //retrun 0
// 	return (current_quotation);
// }

// // "lol">lol
// int save_token_or_return_start(int *i, int token_start, t_data *data)
// {
// 	int separator_found;

// 	separator_found = isseparator(data->raw_input, (*i));
// 	if (separator_found)
// 	{			
// 		// printf("%c\n", data->raw_input[*i]);
// 		if ((*i) != 0 && !isseparator(data->raw_input, (*i) - 1)) // separator not on the beginning and NO SEPARATOR before
// 			{
// 				printf("word found at index %d, we need to save it as a token\n", token_start);
// 			}
// 		if (separator_found == PIPE || separator_found == IN || separator_found == OUT
// 			|| separator_found == HERED || separator_found == APPEND || separator_found == END)
// 		{
// 			{
// 				printf("separator found at index %d, we need to save it as a token\n", *i);
// 			}
// 			if (separator_found == HERED || separator_found == APPEND)
// 				(*i)++; // why *i++ doesnt wprk
// 		}
// 		token_start = (*i)++;


// 	}
// 	return(token_start);
// }

// int	tokenizer(t_data *data)
// {
// 	int i;
// 	int current_quotation;
// 	int input_end_idx; // where \0 will be
// 	int token_start;

// 	input_end_idx = ft_strlen(data->raw_input);
// 	// printf("end of input: %d\n", input_end);
// 	i = 0;
// 	token_start = 0;
// 	current_quotation = 0;

// 	while (i <= input_end_idx) // i is always increased but token_start we get from function
// 	{
// 		current_quotation = check_quotation(current_quotation, data->raw_input, i); 
// 		//if quotation is open -> i++, try to find matching quotation
// 		// // printf("quotation status %d\n", current_quotation);

// 		if (current_quotation == NONE_OR_CLOSED)
// 			token_start = save_token_or_return_start(&i, token_start, data);
	
// 		i++;
// 	}
// 	if (current_quotation != NONE_OR_CLOSED)
// 		{
// 			printf("error: minishell doesn't support unclosed quotation\n");
// 			return (0);
// 		}
// 	return (1);

// }

