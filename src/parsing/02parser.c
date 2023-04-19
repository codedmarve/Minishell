
#include "../../includes/minishell.h"

void	print_full_token_data(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token_lst;
	i = 0;
	while (tmp)
	{
		printf("TOK %i:%s TOK_TYPE:%d\n",
			i, tmp->string, tmp->type);
		// printf("TOK %i:%s TOK_TYPE:%d QUOT:%d\n",
		// 	i, tmp->string, tmp->type, tmp->quote_type);
		i++;
		tmp = tmp->next;
	}
}

void	print_token_string(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token_lst;
	i = 0;
	while (tmp)
	{
		printf("%s ", tmp->string);
		i++;
		tmp = tmp->next;
	}
	printf("\n");
}

/// @brief takes a pointer to a string input and removes consecutive quotes
/// of the same type (either single or double quotes) from it.
///nIt does this by iterating through the string character by character,
/// keeping track of whether it is currently inside a quoted section or not.
/// 
/// If it encounters two consecutive quotes of the same type (i.e. " " or ' '),
/// it skips the second quote and continues iterating.
///
/// If it encounters a quote that starts a new quoted section,
/// it toggles the in_q variable accordingly.
///
/// After iterating through the entire string,
/// it writes a null character '\0' at the end to terminate the resulting str.
///
/// Note that this function modifies the input string in place,
/// so any changes made to input inside this function will be reflected
/// in the original variable that was passed in:
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

void	free_token_lst(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (*token_lst != NULL)
	{
		if (tmp->string)
			free(tmp->string);
		tmp = tmp->next;
		free(*token_lst);
		*token_lst = tmp;
	} // free(token_lst) here???
}

// /// @brief counts the number of pipes (|) present in the 
// /// input token list, which is used to determine the number 
// /// of commands that will be executed in a pipeline.
// /// @param token_lst 
// /// @return nr. of commands (nr. of pipes + 1)
int cmd_counter(t_token *token_lst)
{
    t_token *tmp;
    int     i;

    tmp = token_lst;
    i = 1;
    while (tmp != NULL)
    {
        if (tmp->type == PIPE)
            i++;
        tmp = tmp->next;
    }
    return (i);
}


int	allocate_cmds(t_data *data)
{
    int cmds;
    int i;
    t_cmd *cmd;

    cmds = cmd_counter(data->token_lst);
    data->cmds = (t_cmd **)malloc(sizeof(t_cmd *) * (cmds + 1));
    // if (!data->cmds)
    i = 0;
    while (i < cmds)
    {
        cmd = malloc(sizeof(t_cmd));
        cmd->cmd_splitted = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->infiles = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->outfiles = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->heredocs = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->appends = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->fd_infile = 0;
        cmd->fd_outfile = 1;
        cmd->cmd_idx = i;
        data->cmds[i] = cmd;
        i++;
    }
    data->cmds[i] = NULL; // Set the last element of the array to NULL
	return (0);
}

void handle_token(t_token *token, t_cmd *cmd, int token_idx)
{
    if (token->type == WORD)
        cmd->cmd_splitted[token_idx] = token->string;
    else if (token->type == IN_RED)
        cmd->infiles[token_idx] = token->string;
    else if (token->type == OUT_RED)
        cmd->outfiles[token_idx] = token->string;
    else if (token->type == HERE_DOC)
        cmd->heredocs[token_idx] = token->string;
    else if (token->type == APP_RED)
        cmd->appends[token_idx] = token->string;
}


void create_cmds(t_data *data)
{
    int cmd_idx;
    int token_idx;
    t_token *current_token;
    t_cmd *current_cmd;

	cmd_idx = 0;
    token_idx = 0;
    current_token = data->token_lst;
    current_cmd = data->cmds[cmd_idx];
    while (current_token != NULL)
    {
        if (current_token->type == PIPE)
        {
            cmd_idx++;
            token_idx = 0;
            current_cmd = data->cmds[cmd_idx];
        }
        else if (current_token->type != SEP)
        {
            handle_token(current_token, current_cmd, token_idx);
            token_idx++;
        }
        current_token = current_token->next;
    }

	int i = 0;
	while (i < cmd_counter(data->token_lst))
	{
		printf("i: %d in: %d out: %d\n", i, data->cmds[i]->fd_infile, data->cmds[i]->fd_outfile);
		int j = 0;
		while (data->cmds[i]->cmd_splitted[j])
		{
			printf("cmd: %s\n", data->cmds[i]->cmd_splitted[j]);
			j++;
		}
		i++;
	}
}


// void create_cmds(t_data *data)
// {
// 	int cmd_idx;
//     int token_idx;
//     t_token *current_token;
// 	t_cmd *current_cmd;

// 	cmd_idx = 0;
//     token_idx = 0;
//     current_token = data->token_lst;
//     while (current_token != NULL)
//     {
//         if (current_token->type == PIPE)
//         {
//             cmd_idx++;
//             token_idx = 0;
//         }
//         else if (current_token->type != SEP)
//         {
//             current_cmd = data->cmds[cmd_idx];

//             if (current_token->type == WORD)
//                 current_cmd->cmd_splitted[token_idx] = current_token->string;
//             else if (current_token->type == IN_RED)
//                 current_cmd->infiles[token_idx] = current_token->string;
//             else if (current_token->type == OUT_RED)
//                 current_cmd->outfiles[token_idx] = current_token->string;
//             else if (current_token->type == HERE_DOC)
//                 current_cmd->heredocs[token_idx] = current_token->string;
//             else if (current_token->type == APP_RED)
//                 current_cmd->appends[token_idx] = current_token->string;
//             token_idx++;
//         }
//         current_token = current_token->next;
//     }
// 	int i = 0;
// 	while (i < cmd_counter(data->token_lst))
// 	{
// 		printf("i: %d in: %d out: %d\n", i, data->cmds[i]->fd_infile, data->cmds[i]->fd_outfile);
// 		int j = 0;
// 		while (data->cmds[i]->cmd_splitted[j])
// 		{
// 			printf("cmd: %s\n", data->cmds[i]->cmd_splitted[j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }
	// int i = 0;
	// while (i < cmd_counter(data->token_lst))
	// {
	// 	printf("i: %d in: %d out: %d\n", i, data->cmds[i]->fd_infile, data->cmds[i]->fd_outfile);
	// 	int j = 0;
	// 	while (data->cmds[i]->cmd_splitted[j])
	// 	{
	// 		printf("cmd: %s\n", data->cmds[i]->cmd_splitted[j]);
	// 		j++;
	// 	}
	// 	i++;
	// }


//	interpreter(data); // fills smd_struct
int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	tokenizer(&data->token_lst, data->input);
	expand_token_lst(&data->token_lst);
//	print_full_token_data(data);
//	redirect_handler(&data->token_lst); // returns 0
 	allocate_cmds(data);
	create_cmds(data);
	free_token_lst(&data->token_lst);
	return (0);
}
