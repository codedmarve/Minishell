// char *expand_token(char *token)

// {
//     char *new;
// 	int i;
// 	int j;
// 	char *exit_status;
// 	char var[1000];
	
// 	new = malloc(10000);
//     // if (!new)
// 	// return NULL;
//     i = 0;
//     j = 0;
//     while (token[i] != '\0')
// 	{
//         if (token[i] == '$')
// 		{
//             if (token[i+1] == '?')
// 			{
//                 exit_status = get_exit_status();
//                 ft_strcpy(&new[j], exit_status);
//                 j += ft_strlen(exit_status);
//                 free(exit_status);
//                 i += 2;
//             }
// 			else if (token[i+1] == '$')
// 			{
//                 new[j++] = '$';
//                 i += 2;
//             }
// 			else 
// 			{
//                 int k = i + 1;
//                 int var_len = 0;
//                 while (token[k] != '\0' && token[k] != '$' && token[k] != ' ') {
//                     var[var_len++] = token[k++];
//                 }
//                 var[var_len] = '\0';
//                 char *env_var = getenv(var);
//                 if (env_var != NULL) {
//                     strcpy(&new[j], env_var);
//                     j += strlen(env_var);
//                 }
//                 i = k;
//             }
//         } else {
//             new[j++] = token[i++];
//         }
//     }
//     new[j] = '\0';
//     return new;
// }