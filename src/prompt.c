#include "../includes/minishell.h"

/*
add_history() from readline library saves command history
no extra actions needed

with readline we can read a line from the terminal (similar to scanf)
-> https://de.wikipedia.org/wiki/GNU_readline
readline function mallocs -> needs to get freed in the end
flag to compile readline correctly: -lreadline

functions we can use:
rl_clear_history
*/

char	*get_prompt(void)
{
	char	*prompt;
	char	*input;

	prompt = "minishell$ ";
	input = readline(prompt);
	if (ft_strlen(input) > 0)
	{
		// printf("%s\n", input); 
		add_history(input); // create history
	}
	return (input);
}
// int	get_prompt2(char **env, t_data *data, char *pwd, int *fd)
// {
// 	int		i;
// 	char	*tmp;
// 	char 	*tmp2;

// 	i = 0;
// 	read(fd[0], pwd, 1000);
// 	pwd[ft_strlen(pwd) - 1] = '\0';
// 	while(env[i])
// 	{
// 		if (ft_strncmp(env[i], "USER=", 5) == 0)
// 		// daria: changed to libft function
// 		// if (strncmp(env[i], "USER=", 5) == 0)
// 		{
// 			tmp = ft_strjoin(&env[i][5], "@minishell:\e[1;34m");
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (!tmp)
// 		tmp = ft_strdup("user@minishell:\e[1;34m");
// 	tmp2 = ft_strjoin(pwd, "\033[0m$ ");
// 	data->prompt = ft_strjoin(tmp, tmp2);
// 	return (free(tmp), free(tmp2), 1);
// }


// int	get_prompt(char **env, t_data *data)
// {
// 	int		fd[2];
// 	char	pwd[1000];
// 	char	**cmd_mac;
// 	char	**cmd_linux;

//     pipe(fd);
// 	ft_bzero(pwd, 1000);
// 	cmd_mac = ft_split("/bin/pwd", ' ');
// 	cmd_linux = ft_split("/usr/bin/pwd", ' ');
// 	if (fork() == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		if (access("/usr/bin/pwd", X_OK) == 0)
// 			execve("/usr/bin/pwd", cmd_linux, NULL);
// 		else if (access("/bin/pwd", X_OK) == 0)
// 			execve("/bin/pwd", cmd_mac, NULL);
// 		else
// 			return (ft_printf("-"), 0);
// 	}
// 	get_prompt2(env, data, pwd, fd);
// 	free(cmd_linux[0]);
// 	free(cmd_mac[0]);
// 	free(cmd_linux);
// 	free(cmd_mac);
// }
