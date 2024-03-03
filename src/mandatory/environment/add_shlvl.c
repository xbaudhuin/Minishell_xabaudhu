#include "minishell.h"

void	add_shlvl(t_env env)
{
	char	*argv[3];

	argv[0] = "export";
	argv[1] = "SHLVL=1";
	argv[2] = NULL;
	export((const char **)argv, &env);
}