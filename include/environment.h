#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

typedef struct s_env
{
	char	**variables;
	size_t	allocated_size;
}			t_env;

t_env	create_env(const char **main_env);
void	free_env(t_env env);
char	*ft_getenv(const char *name, const t_env env);
t_env	get_expended_env(t_env old_env, int *ext_sts);

#endif