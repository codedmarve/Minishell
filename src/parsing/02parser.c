
#include "../../includes/minishell.h"

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

/// @brief 
/// allocate array of struct*
/// allocate structs corresponding to each struct*
/// allocate array of char* corresponding to each struct, 
/// those will be dynamically changed later
/// @param data 
/// @return 
int	alloc_arr_with_2d(t_data *data)
{
    int cmds;
    int i;
    t_cmd *cmd;

    cmds = cmd_counter(data->token_lst);
    data->cmds = ft_calloc((cmds + 1), sizeof(t_cmd *));
    // if (!data->cmds)
    i = 0;
    while (i < cmds)
    {
        cmd = ft_calloc(1, sizeof(t_cmd));
        cmd->cmd_splitted = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->infiles = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->outfiles = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->heredocs = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
        cmd->appends = ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
		// (if !)
        cmd->fd_infile = 0;
        cmd->fd_outfile = 1;
  //      cmd->cmd_idx = i;
        data->cmds[i] = cmd;
        i++;
    }
    data->cmds[i] = NULL; // Set the last element of the array to NULL
	return (0);
}

/// @brief note that this implementation uses NULL to indicate an empty list, 
/// but it's possible also use a sentinel node as a placeholder.
/// @param data 
/// @return 
int alloc_arr_w_lists(t_data *data) 
{
	int cmds;
    int i;
    t_cmd *cmd;

    cmds = cmd_counter(data->token_lst);
    data->cmds = ft_calloc((cmds + 1), sizeof(t_cmd *));
	// if (!data->cmds)
    i = 0;
    while (i < cmds) 
	{
        cmd = ft_calloc(1, sizeof(t_cmd));
		//if (!cmd)
        cmd->cmd_splitted = (char **)ft_calloc(MAX_TOKENS_PER_TYPE, sizeof(char *));
		// if (!cmd->cmd_splitted)
        cmd->infiles = NULL;
        cmd->outfiles = NULL;
        cmd->heredocs = NULL;
        cmd->appends = NULL;
        cmd->fd_infile = 0;
        cmd->fd_outfile = 1;
 //       cmd->cmd_idx = i;
        data->cmds[i] = cmd;
        i++;
    }
    data->cmds[i] = NULL; // Set the last element of the array to NULL
	i = 0;
	while (i < cmd_counter(data->token_lst))
	{
		printf("i: %d in: %d out: %d\n", i, data->cmds[i]->fd_infile, data->cmds[i]->fd_outfile);
		i++;
	}
	return(0);
}

int	parser(t_data *data)
{
	remove_consequtive_quotes(data->input);
	tokenizer(&data->token_lst, data->input);
	expand_token_lst(&data->token_lst);
//	print_full_token_data(data);
//	redirect_handler(&data->token_lst); // returns 0
	alloc_arr_w_lists(data);
//	create_cmds(data);
	free_token_lst(&data->token_lst);
	return (0);
}


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
		// j = 0;
		// while (data->cmds[i]->infiles[j])
		// {
		// 	printf("ins: %s\n", data->cmds[i]->infiles[j]);
		// 	j++;
		// }
		// j = 0;
		// while (data->cmds[i]->outfiles[j])
		// {
		// 	printf("outs: %s\n", data->cmds[i]->outfiles[j]);
		// 	j++;
		// }
		// while (data->cmds[i]->heredocs[j])
		// {
		// 	printf("heredocs: %s\n", data->cmds[i]->heredocs[j]);
		// 	j++;
		// }
		// j = 0;
		// while (data->cmds[i]->appends[j])
		// {
		// 	printf("appends: %s\n", data->cmds[i]->appends[j]);
		// 	j++;
		// }
// 		i++;