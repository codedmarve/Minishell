
#include "../includes/minishell.h"

// int	g_exit_status = 0;

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

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	welcome(ac, av);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (printf("Error: malloc failure (main)"), 1);
	envplist_handler(&data->env_lst, envp);
	while (1)
	{
		data->input = readline("minishell$ ");
		if (ft_strlen(data->input) > 0)
		{
			add_history(data->input);
			input_handler(data);
		}
		else
			free(data->input);
	}
	return (0);
}
