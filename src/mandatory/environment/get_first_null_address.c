#include "minishell.h"

char	**get_first_null_address(const t_env env)
{
	int	var_num;

	var_num = env.allocated_size - 1;
	while (var_num > 0)
	{
		if (env.variables[var_num] != NULL)
		{
			break ;
		}
		--var_num;
	}
	return (&env.variables[var_num]);
}
