
#include "../../includes/minishell.h"

/* ERROR HANDLING:
bash: syntax error near unexpected token `&'
*/


/* 
Minishell does not support \, ;, &&, ||, or wildcards.

we need to implement:

' ' single quotes prevent from interpreting special chars
(echo '$PATH' outputs '$PATH' on the screen)

" " double quotes prevent from interpreting special chars except $
(echo "$PATH" equal to echo $PATH)
if " ls " - command not found

QUOTES + SPACES
' ls '
bash:  ls : command not found
" ls "
bash:  ls : command not found

PIPES
REDIRECTIONS > >> < <<
do not need

$?
*/

/* OPTIONAL
!
#*/
