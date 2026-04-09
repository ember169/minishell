/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:08:28 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/08 16:15:52 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Potential performances improvements: 
	- refactor extract_key and extract_value in a single function
	- only one allocation instead of three ?
*/

#include "../../includes/includes.h"

static char	*_extract_key(char *env)
{
	char	*key;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, env, i + 1);
	return (key);
}

static char	*_extract_value(char *env)
{
	char	*value;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
		i++;
	if (env[i] != '\0')
	{
		value = ft_strdup(&env[i]);
		if (!value)
			return (NULL);
	}
	else
		value = ft_strdup("");
	return (value);
}

t_env	*create_node(char *env)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->key = _extract_key(env);
	ret->value = _extract_value(env);
	ret->next = NULL;
	return (ret);
}

/*
** init_env_vars:
**     Iterate through mandatory env values to make sure they are set
**
**     @param *ms  Minishell super structure
**     @return 1 / -1 in case of error
*/
static int	_check_env_vars(t_minishell *ms, char *av0)
{
	printf("\n========= ENV VARS INIT DEBUG =========\n\n┌ Initializing:\n");
	if (!check_env_pwd(ms))
		return (-1);
	if (!check_env_old_pwd(ms))
		return (-1);
	if (!check_env_path(ms))
		return (-1);
	if (!check_env_underscore(ms, av0))
		return (-1);
	if (!check_env_shlvl(ms))
		return (-1);
	printf("└ Env vars init done !\n");
	return (1);
}

/*
** init_env:
**     Initializes t_env list:
**	   - With extern environ global variable
**	   - If environ empty (env -i ./minishell), sets minimal requirements nodes
**
**     @return Pointer to newly created env list root.
*/
t_env	*init_env(t_minishell *ms, char *av0)
{
	int		i;

	ms->env_list = NULL;
	if (environ && environ[0])
	{
		i = 0;
		while (environ[i])
		{
			env_add_back(&ms->env_list, create_node(environ[i]));
			i++;
		}
	}
	if (!_check_env_vars(ms, av0))
		return (NULL);
	return (ms->env_list);
}
