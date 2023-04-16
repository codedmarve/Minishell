
#include "../../includes/minishell.h"

/// @brief  initializes the exit status by getting it using get_exit_status(),
/// copies the exit status to the new_ptr at the index
/// specified by j_ptr and updates j_ptr to point to the end of the new string.
///
/// It then frees the memory allocated for exit_status.
/// Finally, it updates i_ptr to the index after the "$?" characters.
/// @param new_ptr 
/// @param j_ptr 
/// @param i_ptr 
void	init_exit_status(char **new_ptr, int *j_ptr, int *i_ptr)
{
	char	*exit_status;

	exit_status = get_exit_status();
	ft_strcpy(&(*new_ptr)[*j_ptr], exit_status);
	*j_ptr += ft_strlen(exit_status);
	free(exit_status);
	*i_ptr += 2;
}

/// @brief handles a single dollar sign in a token string 
/// by adding it to the expanded token and incrementing the index ptr by 2.
/// @param new_ptr 
/// @param j_ptr 
/// @param i_ptr 
void	init_single_dollar(char **new_ptr, int *j_ptr, int *i_ptr)
{
	(*new_ptr)[(*j_ptr)++] = '$';
	*i_ptr += 2;
}

/// @brief expands the remaining tokens of the string token 
/// that start with the $ character.
/// If the next character after the $ is ?,
/// it initializes the exit status by calling the init_exit_status(). 
/// If it's $, it initializes the $ by calling the init_single_dollar().
/// Otherwise, it initializes the env variable by calling the init_env_var().
/// Keeps expanding the remaining tokens as long as the next character is a $.
/// Updates the pointers j_ptr and i_ptr accordingly.
/// @param new_ptr 
/// @param j_ptr 
/// @param i_ptr 
/// @param token 
void	expand_remainder(char **new_ptr, int *j_ptr,
	int *i_ptr, char *token)
{
	while (token[*i_ptr] == '$')
	{
		if (token[*i_ptr + 1] == '?')
			init_exit_status(new_ptr, j_ptr, i_ptr);
		else if (token[*i_ptr + 1] == '$')
			init_single_dollar(new_ptr, j_ptr, i_ptr);
		else
			init_env_var(new_ptr, j_ptr, i_ptr, token);
	}
}

/// @brief Initializes an env variable in the expanded token string.
/// It takes four arguments:
/// @param new_ptr ptr to a ptr to the beginning of the new string.
/// @param j_ptr ptr to the index of the current char in the new string.
/// @param i_ptr ptr to the index of the current char in the original token str.
/// @param token the original token string.
///
/// extracts the name of the env var by parsing the str following the "$" char,
/// then checks if the env var exists and if it does,
/// it appends the value of the env var to the new string. 
/// Finally, it expands any remaining "$" chars in the original str by calling 
/// the `expand_remainder` function.
///
/// If no valid environment variable name is found,
/// the function simply returns without modifying the new string.
///
/// Does not return anything,
/// but it modifies the `new_ptr`, `j_ptr`, and `i_ptr` ptr's
/// indirectly by updating the new string and the current indices
/// in the original and new str.
void	init_env_var(char **new_ptr, int *j_ptr, int *i_ptr, char *token)
{
	int		k;
	char	*var;
	int		var_len;
	char	*env_var;

	k = *i_ptr + 1;
	var = malloc(ft_strlen(token) + 1); // if !var
	var_len = 0;
	while (ft_isalnum(token[k]))
		var[var_len++] = token[k++];
	if (var_len == 0) // no valid environment variable name found
	{
		free(var);
		return ;
	}
	var[var_len] = '\0';
	env_var = getenv(var);
	if (env_var != NULL)
	{
		ft_strcpy(&(*new_ptr)[*j_ptr], env_var);
		*j_ptr += ft_strlen(env_var);
	}
	expand_remainder(new_ptr, j_ptr, &k, token);
	*i_ptr = k;
	free(var);
}

/// @brief takes in a character c and copies it to the new_ptr string
/// at the index specified by j_ptr. 
/// It then increments j_ptr by 1 to indicate that the next char
/// should be written to the next index in the string.
///
/// @param new_ptr pointer to the string where the new token will be stored
/// @param j_ptr pointer to an integer representing the current index in new_ptr
/// @param c  the character to be copied to the new token
void	copy_token_char(char **new_ptr, int *j_ptr, char c)
{
	(*new_ptr)[(*j_ptr)++] = c;
}

//// NO NORM! but could handle bonus part in this implementation  -
////"$USER'$USER'"
//
// void init_env_var(char** new_ptr, int* j_ptr, int* i_ptr, char* token) {
//     int k = *i_ptr + 1;
//     char *var = malloc(ft_strlen(token) + 1);
//     int var_len = 0;

//     while (ft_isalnum(token[k])) {
//         var[var_len++] = token[k++];
//     }

//     if (var_len == 0) {
//         // No valid environment variable name found
//         free(var);
//         return;
//     }

//     var[var_len] = '\0';

//     char* env_var = getenv(var);

//     if (env_var != NULL) {
//         strcpy(&(*new_ptr)[*j_ptr], env_var);
//         *j_ptr += ft_strlen(env_var);
//     }

//     // If there are more $ characters, keep expanding
//     while (token[k] == '$') {
//         if (token[k + 1] == '?') {
//             init_exit_status(new_ptr, j_ptr, &k);
//         } else if (token[k + 1] == '$') {
//             init_single_dollar(new_ptr, j_ptr, &k);
//         } else {
//             init_env_var(new_ptr, j_ptr, &k, token);
//         }
//     }

//     *i_ptr = k;
//     free(var);
// }

/// /// couldnt handle bonus part in this implementation  - "$USER'$USER'"
// void	init_env_var(char **new_ptr, int *j_ptr, int *i_ptr, char *token)
// {
// 	int		k;
// 	char	var[1000];
// 	int		var_len;
// 	char	*env_var;

// 	k = *i_ptr + 1;
// 	var_len = 0;
// 	while (token[k] != '\0' && token[k] != '$' && token[k] != ' ')
// 	{
// 		var[var_len++] = token[k++];
// 	}
// 	var[var_len] = '\0';
// 	env_var = getenv(var);
// 	if (env_var != NULL)
// 	{
// 		ft_strcpy(&(*new_ptr)[*j_ptr], env_var);
// 		*j_ptr += strlen(env_var);
// 	}
// 	*i_ptr = k;
// }