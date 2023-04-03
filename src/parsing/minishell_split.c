
#include "../../includes/minishell.h"

int	str_counter(char *string, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 1;
	while (string[i])
	{
		if (!quotes_are_closed(string[i]))
		{
			i++;
			continue ;
		}
		if (string[i] == c)
			counter++;
		i++;
	}
	quotes_default();
	return (counter);
}

char	*init_str(char *s, char c)
{
	int		strlen;
	char	*str;

	strlen = 0;
	while (s[strlen])
	{
		if (quotes_are_closed(s[strlen]) && s[strlen] == c)
			break ;
		strlen++;
	}
	if (strlen == 0)
	{
		quotes_default();
		return (NULL);
	}
	str = ft_calloc(strlen + 1, sizeof(char));
	str = ft_memcpy(str, s, strlen);
	quotes_default();
	return (str);
}

char	**modified_split(char *s, char c)
{
	int i = -1;
	int count = 0;
	char *temp;
	char **splitted;

	if (!s)
		return (NULL);
	splitted = ft_calloc((str_counter(s, c) + 1), sizeof(char *));
	if (splitted == NULL)
		return (NULL);
	while (s[++i])
	{
		if (count && quotes_are_closed(s[i - 1]) == false)
			continue ;
		if (s[i] == 0)
			break ;
		if (count == 0 || s[i - 1] == c)
		{
			temp = init_str(s + i, c);
			if (temp)
				splitted[count++] = temp;
		}
	}
	quotes_default();
	splitted[count] = NULL;
	return (splitted);
}
/* 
if there is a pipe on the begining or the end,
it will be treated as an error 
PIPE text PIPE will give amt of 3 words, but it will be not processed by our code
*/

// size_t	mini_word_counter(const char *s, char c)
// {
// 	size_t	word_counter;

// 	if (!*s)
// 		return (0);
// 	word_counter = 0;
// 	while (*s)
// 	{
// 		if (!quotes_are_closed(*s))
// 		{
// 			s++;
// 			continue ;
// 		}
// 		if (*s != c && ((*(s + 1)) == c || (*(s + 1)) == '\0'))
// 			word_counter++;
// 		s++;
// 	}
// 	quotes_default();
// 	return (word_counter);
// }

// /*
// 1. count word length + allocate memory for it (incl NULL terminator)
// 2. copies chars from an original str to new placem return ptr to it
// 3. nothing is happening to orig. string  - we need to move among that using ft_split function
// */
// char	*mini_write_words(const char *str, char c)
// {
// 	int		i;
// 	char	*word;

// 	i = 0;
// 	while (str[i] && str[i] != c)
// 		i++;
// 	word = malloc(sizeof(char) * (i + 1));
// 	if (!word)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] && str[i] != c)
// 	{
// 		word[i] = str[i];
// 		i++;
// 	}
// 	word[i] = '\0';
// 	return (word);
// }

// /*
// 1. count words using ft_word_counter + allocate memory for that
// */
// char	**mini_split(char const *s, char c)
// {
// 	char	**splitted;
// 	int		i;
// 	int		words;

// 	if (!s)
// 		return (NULL);
// 	words = mini_word_counter(s, c);
// 	splitted = malloc(sizeof(char *) * (words + 1));
// 	if (!splitted)
// 		return (NULL);
// 	i = 0;
// 	while (i < words)
// 	{
// 		while (*s && *s == c && !quotes_are_closed(*s))
// 			s++;
// 		splitted[i] = mini_write_words(s, c);
// 		while (*s && *s != c)
// 			s++;
// 		i++;
// 	}
// 	quotes_default();
// 	splitted[i] = NULL;
// 	return (splitted);
// }

// int	str_counter(char *input, char delimiter) // google pls static/const
// {
// 	int		counter;

// 	// if (!*input) //PLEASE DO IT IN GLOBAL SPLIT FUNCTION
// 	// 	return (0);
// 	counter = 0;
// 	while (*input)
// 	{
// 		if (!quotes_are_closed(*input))
// 		{
// 			input++;
// 			continue ;
// 		}
// 		if (*input == delimiter)
// 			counter++;
// 		input++;
// 	}
// 	quotes_default();
// 	return (counter);
// }

// static char	*copy_single_str(char *input, char delimiter) //google const char pls
// {
// 	int		strlen;
// 	char	*str;

// 	strlen = 0;
// 	while (*input)
// 	{
// 		if (quotes_are_closed(*input) && *input == delimiter)
// 			break ;
// 		strlen++;
// 		input++;
// 	}
// 	if (!strlen)
// 	{
// 		quotes_default();
// 		return (0);
// 	}
// 	str = ft_calloc(strlen + 1, sizeof(char));
// 	str = ft_memcpy(str, input, strlen);
// 	quotes_default();
// 	return (str);
// }

// char	**minishell_split(char *input, char delimiter)
// {
// 	char **splitted;
// 	char *temp;
// 	int i = -1;
// 	int count = 0;
// 	if (!input)
// 		return (NULL);

// 	splitted = ft_calloc((str_counter(input, delimiter) + 1), sizeof(char *));
// 	if (splitted == NULL)
// 		return (NULL);
// 	while (input[++i])
// 	{
// 		if (count && quotes_are_closed(input[i - 1]) == false)
// 			continue ;
// 		if (input[i] == 0)
// 			break ;
// 		if (count == 0 || input[i - 1] == delimiter)
// 		{
// 			temp = copy_single_str(input + i, delimiter);
// 			if (temp)
// 				splitted[count++] = temp;
// 		}
// 	}
// 	quotes_default();
// 	splitted[count] = NULL;
// 	return (splitted);
// }