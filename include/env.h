#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env
{
	char	**variables;
	size_t	allocated_size;
}			t_env;



#endif