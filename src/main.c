
#include "../includes/minishell.h"

int	exit_status = 0;

void	welcome(int argc, char **argv)
{
	if (argc > 1 || argv[1])
		exit(printf("error: minishell can't take argument(s)\n") - 39);
	printf("%s   ****************************************\n",
		"\033[0;32m");
	printf("   *        welcome to minishell          *\n");
	printf("   *%s   created by marvellous and daria    %s*\n",
		"\033[0;33m", "\033[0;32m");
	printf("   ****************************************\n%s",
		"\033[0m");
}

void	init_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->token_lst = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	welcome(ac, av);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error: malloc failure (main)"), 1);
	init_data(data, envp);
	while (1)
	{
		data->input = readline("minishell$ ");
		if (ft_strlen(data->input) > 0)
			add_history(data->input);
		input_handler(data);
	}
	free (data);
	return (0);
}
