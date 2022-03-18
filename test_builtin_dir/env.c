#include "test_builtin.h"

int	my_env(t_envlist *envlist)
{
	while (envlist)
	{
		if (envlist->value == NULL)
		{
			envlist = envlist->next;
			continue ;
		}
		printf("%s=%s\n", envlist->key, envlist->value);
		envlist = envlist->next;
	}
	return (0);
}
