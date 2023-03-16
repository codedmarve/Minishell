#include "../includes/minishell.h"

void	welcome(int argc, char **argv)
{
	if (argc > 1 || argv[1])
		exit(printf("Error: programme can't take argument(s)\n") - 39);
	printf("%s   ****************************************\n",
		"\033[0;32m");
	printf("   *   Welcome to Minishell               *\n");
	printf("   *                                      *\n");
	printf("   *%s   Created by Marvellous and Daria    %s*\n",
		"\033[0;33m", "\033[0;32m");
	printf("   ****************************************\n%s",
		"\033[0m");
}
