
#include "../../includes/minishell.h"

/// @brief expands environment variables in a given string token.
/// It returns a new string with the expanded variables.
/// If no environment variables are found, the original token is returned.
/// The expanded string is allocated on the heap, 
/// so it should be freed after use.
///
/// 'trasforms'consecutive $$ into $
/// bash expands $$ as PID - we don't need to implement it
///  
/// @param token 
/// @return 
char	*expand_token(char *token)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(MAX_TOKEN_SIZE); // if !new
	i = 0;
	j = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			if (token[i + 1] == '?')
				init_exit_status(&new, &j, &i);
			else if (token[i + 1] == '$')
				init_single_dollar(&new, &j, &i);
			else
				init_env_var(&new, &j, &i, token);
		}
		else
			copy_token_char(&new, &j, token[i++]);
	}
	new[j] = '\0';
	return (new);
}

/// @brief  loops through a linked list of tokens 
/// and expands any token that contains a dollar sign. 
///
/// If the token has single quotes around it, the dollar sign is not expanded. 
/// @param token_lst 
void	expand_token_lst(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (tmp != NULL)
	{
		if (tmp->quote_type != S_Q && dollar_in_str(tmp->string))
			tmp->string = expand_token(tmp->string);
		tmp = tmp->next;
	}
}
