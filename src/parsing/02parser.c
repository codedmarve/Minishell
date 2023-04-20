
#include "../../includes/minishell.h"


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

        // printf("\tCMD SPLITTED:\n");
        // for (j = 0; cmd->cmd_splitted[j] != NULL; j++)
        //     printf("\t\t[%d]: %s\n", j, cmd->cmd_splitted[j]);

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

void create_cmds(t_data *data)
{
	t_token *current_token;
	int current_cmd_index;

	current_token = data->token_lst;
    current_cmd_index = 0;
    while (current_token != NULL)
    {
        if (current_token->type == PIPE)
        {
            current_cmd_index++;
            current_token = current_token->next;
            continue;
        }
        if (current_token->type == SEP)
        {
            current_token = current_token->next;
            continue;
        }
        add_token_to_cmd(&(data->cmds[current_cmd_index]), current_token);
        current_token = current_token->next;
    }
}

int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	tokenizer(&data->token_lst, data->input);
	expand_token_lst(&data->token_lst);
	print_full_token_data(data);

//	redirect_handler(&data->token_lst); // returns 0
	allocate_cmds(data);
	create_cmds(data);
	print_data(data);
	free_token_lst(&data->token_lst);
	return (0);
}
