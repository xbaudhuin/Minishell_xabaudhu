#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_env
{
	char	**variables;
	size_t	allocated_size;
	int		pwd_unset_time;
	int		was_oldpwd_unset;
	int		exit_status;
}			t_env;

# define OLD 1
# define NEW 2

t_env	create_env(const char **main_env);
void	free_env(t_env *env);
char	*ft_getenv(const char *name, const t_env env);
char	**get_line_address(const char *name, const t_env env);
t_env	get_expended_env(t_env old_env, int *ext_sts);
char	**get_line_address(const char *name, const t_env env);

#endif