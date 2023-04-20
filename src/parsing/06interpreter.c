

// #include "../../includes/minishell.h"

// /// @brief counts the number of arguments 
// /// in the token list until a pipe is encountered
// /// @param token_lst 
// /// @return 
// int	arg_counter(t_token **token_lst)
// {
// 	t_token	*tmp;
// 	int		i;

// 	tmp = *token_lst;
// 	i = 0;
// 	while (tmp != NULL && tmp->type != PIPE)
// 	{
// 		if (tmp->type == WORD)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// // void init_cmd

// int	interpreter(t_data *data)
// {
// 	t_token *tmp;
// 	int		 cmd_idx;
// 	int i;


// 	tmp = data->token_lst;
// 	// while (tmp != NULL)
// 	// {
// 	// 	printf("%s\n", tmp->string);
// 	// 	tmp = tmp->next;
// 	// }
// 	return (0);
// }

