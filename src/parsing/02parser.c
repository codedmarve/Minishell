
#include "../../includes/minishell.h"

/*
Use the function count_cmds to count the number of t_cmd structs required based on the number of PIPE tokens in the token list.
Allocate memory for the array of t_cmd structs using calloc, based on the count returned by count_cmds.
Iterate through the token list and separate the tokens into groups based on the PIPE tokens. Create a new t_cmd struct for each group, and store the relevant tokens in the corresponding struct. Skip tokens of type SEP and PIPE.
For each t_cmd struct, allocate memory for the cmd_splitted 2d array of strings using calloc, and store the *string of tokens of type WORD in it.
For each t_cmd struct, iterate through the token list again and store the *string of tokens of type IN_RED and HERE_DOC in a linked list of t_ins structs, using the here_doc_flag to indicate HERE_DOC tokens. Allocate memory for each t_ins struct using malloc.
For each t_cmd struct, iterate through the token list again and store the *string of tokens of type OUT_RED and APP_RED in a linked list of t_outs structs, using the app_red_flag to indicate APP_RED tokens. Allocate memory for each t_outs struct using malloc.
Set the fd_infile and fd_outfile of each t_cmd struct to 0 and 1, respectively.
After completing the above steps, you should have an array of t_cmd structs that contains all the relevant data from the token list.
*/
// /// @brief counts the number of pipes (|) present in the 
// /// input token list, which is used to determine the number 
// /// of commands that will be executed in a pipeline.
// /// @param token_lst 
// /// @return nr. of commands (nr. of pipes + 1)
int count_cmds(t_token *token_lst)
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


/// @brief note that this implementation uses NULL to indicate an empty list, 
/// but it's possible also use a sentinel node as a placeholder.
/// @param data 
/// @return 
int allocate_cmds(t_data *data) 
{
    int cmds;
    int i;
    t_cmd *cmd;

    cmds = count_cmds(data->token_lst);
    data->cmds = ft_calloc((cmds + 1), sizeof(t_cmd *));
    // if (!data->cmds)
    // {
    //     perror("Failed to allocate memory for data->cmds");
    //     return 1;
    // }
    i = 0;
    while (i < cmds) 
    {
        cmd = ft_calloc(1, sizeof(t_cmd));
        // if (!cmd)
        // {
        //     perror("Failed to allocate memory for cmd");
        //     // Free any previously allocated memory
        //     while (i > 0)
        //     {
        //         i--;
        //         free(data->cmds[i].cmd_splitted);
        //         free(data->cmds[i].ins);
        //         free(data->cmds[i].outs);
        //     }
        //     free(data->cmds);
        //     return 1;
        // }
        cmd->cmd_splitted = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        // if (!cmd->cmd_splitted)
        // {
        //     perror("Failed to allocate memory for cmd->cmd_splitted");
        //     // Free any previously allocated memory
        //     free(cmd);
        //     while (i > 0)
        //     {
        //         i--;
        //         free(data->cmds[i].cmd_splitted);
        //         free(data->cmds[i].ins);
        //         free(data->cmds[i].outs);
        //     }
        //     free(data->cmds);
        //     return 1;
        // }
        cmd->in_heredoc = NULL;
        cmd->out_app = NULL;
        cmd->fd_infile = 0;
        cmd->fd_outfile = 1;
        data->cmds[i] = *cmd;
        i++;
    }
    data->cmds[i].cmd_splitted = NULL;  // set the last element of the array to NULL
    i = 0;
	while (i < count_cmds(data->token_lst))
	{
		printf("i: %d in: %d out: %d\n", i, data->cmds[i].fd_infile, data->cmds[i].fd_outfile);
		i++;
	}
	return (0);
}

void add_word_to_cmd(t_cmd *cmd, char *word)
{
    int i = 0;
    while (cmd->cmd_splitted[i] != NULL)
        i++;
    cmd->cmd_splitted[i] = ft_strdup(word);
}


void add_token_to_cmd(t_cmd *cmd, t_token *token)
{
    if (token->type == IN_RED || token->type == HERE_DOC)
    {

           token_add_back(&cmd->in_heredoc, token);
    }
    else if (token->type == OUT_RED || token->type == APP_RED)
    {

           token_add_back(&cmd->in_heredoc, token);
    }
    // else if (token->type == WORD)
    // {
    //     add_word_to_cmd(cmd, token->string);
    // }
}


void print_data(t_data *data)
{
    int i, j;
    t_cmd *cmd;
    t_token *token;

    for (i = 0; data->cmds[i].cmd_splitted != NULL; i++)
    {
        printf("CMD %d:\n", i);

        cmd = &data->cmds[i];

        printf("\tCMD SPLITTED:\n");
        for (j = 0; cmd->cmd_splitted[j] != NULL; j++)
            printf("\t\t[%d]: %s\n", j, cmd->cmd_splitted[j]);

        printf("\tIN HEREDOC:\n");
        token = cmd->in_heredoc;
        while (token != NULL)
        {
            printf("\t\t%s\n", token->string);
            token = token->next;
        }

        printf("\tOUT APP:\n");
        token = cmd->out_app;
        while (token != NULL)
        {
            printf("\t\t%s\n", token->string);
            token = token->next;
        }

        printf("\tFD INFILE: %d\n", cmd->fd_infile);
        printf("\tFD OUTFILE: %d\n", cmd->fd_outfile);
    }
}

int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	tokenizer(&data->token_lst, data->input);
	expand_token_lst(&data->token_lst);
//	print_full_token_data(data);
//	redirect_handler(&data->token_lst); // returns 0
	create_cmds(data);
	print_data(data);
	free_token_lst(&data->token_lst);
	return (0);
}
