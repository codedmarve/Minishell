

#include "../../includes/minishell.h"

void	print_after_tokenizer(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token_lst;
	i = 0;
	while (tmp)
	{
		printf("TOK %i:%s TOK_TYPE:%d QUOT:%d\n",
			i, tmp->string, tmp->type, tmp->quote_type);
		i++;
		tmp = tmp->next;
	}
}

void	print_after_expansion(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token_lst;
	i = 0;
	while (tmp)
	{
		printf("TOK %i EXP:%s\n", i, tmp->string);
		i++;
		tmp = tmp->next;
	}
}

/// @brief modifies input string, 
/// skips consecutive quotes that are not inside other quotes
/// for example:
/// $''USER becomes $USER 
/// hi""bye becomes hibye
/// doesnt affect consecutive quotes inside other quotes:
/// "    '' " will remain unchanged
/// @param input
void	remove_consequtive_quotes(char *input)
{
	int	i;
	int	j;
	int	in_q;

	i = 0;
	j = 0;
	in_q = 0;
	while (input[i] != '\0')
	{
		if (!in_q && ((input[i] == '"' && input[i + 1] == '"')
				|| (input[i] == '\'' && input[i + 1] == '\'')))
            i += 2;
		else
		{
			if (input[i] == '"' || input[i] == '\'')
				in_q = !in_q;
			input[j] = input[i];
			i++;
			j++;
		}
	}
	input[j] = '\0';
}

/// @brief appends the first n characters of the src string
/// to the end of the dest string.
/// dst must be large enough to accommodate the concatenated string.
/// If the src  is longer than n characters,
/// only the first n characters are appended.
///
/// Note: function does not add a terminating null character 
/// to the concatenated string, so the dst string must be null-terminated
/// before the concatenation. 
///
/// Care must be taken to ensure that the dest is properly initialized 
/// and sized to avoid buffer overflow errors.
void	ft_strncat(char *dest, char *src, int n)
{
	int	dest_len;
	int	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
}


/// @brief copies at most 'n' characters from the string pointed to by 'src'
/// to the memory area pointed to by 'dest'. 
/// If the length of 'src' is less than 'n', 
/// then the remaining characters of 'dest' are filled with null characters.
///
/// @param dest pointer to the memory area where the content is to be copied.
/// @param src pointer to the string which is to be copied.
/// @param n maximum number of characters to be copied from 'src'.
///
/// The function does not return a value.
/// 
/// This function does not check for null pointers.
/// It is the caller's responsibility to ensure that 
/// 'dest' and 'src' point to valid memory locations.
void	ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
        i++;
	}
}



/// @brief checks if string contains $ char
/// @param s 
/// @return 1 if $ found
int dollar_in_str(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}





// typedef struct s_exp {
//     char *data;
//     struct s_exp *next;
// } t_exp;


// t_exp	*exp_last(t_exp *lst)
// {
// 	t_exp	*tmp;

// 	if (!lst)
// 		return (NULL);
// 	tmp = lst;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	return (tmp);
// }

// void	exp_add_back(t_exp **lst, t_exp *new)
// {
// 	if (!lst || !new)
// 		return ;
// 	if (!*lst)
// 		*lst = new;
// 	else
// 		exp_last(*lst)->next = new;
// }

void expand_token(char *s) {

 	return ;
}

void	expand_token_lst(t_token *token_lst)
{
	t_token	*tmp;

	tmp = token_lst;
	while (tmp != NULL)
	{
		if (tmp->quote_type != S_Q && dollar_in_str(tmp->string))
			expand_token(tmp->string);
		tmp = tmp->next;
	}
}

int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	printf("%s\n", data->input);
	tokenizer(&data->token_lst, data->input);
	print_after_tokenizer(data);
	expand_token_lst(data->token_lst);
	// print_after_expansion(data);
	return (0);
}
