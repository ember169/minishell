/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:08:28 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/01 09:36:19 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Potential performances improvements: 
	- refactor extract_key and extract_value in a single function
	- only one allocation instead of three ?
*/

#include "../../includes/includes.h"

char	*extract_key(char *env)
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

char	*extract_value(char *env)
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

/*
** init_env_vars:
**     Iterate through mandatory env values to make sure they are set
**
**     @param *ms  Minishell super structure
**     @return true / false in case of error
*/
static bool	_check_env_vars(t_minishell *ms, char *av0)
{
	if (!check_env_pwd(ms))
		return (false);
	if (!check_env_old_pwd(ms))
		return (false);
	if (!check_env_path(ms))
		return (false);
	if (!check_env_underscore(ms, av0))
		return (false);
	if (!check_env_shlvl(ms))
		return (false);
	return (true);
}

/*
** init_env:
**     Initializes t_env list:
**	   - With third main variable
**	   - If env empty (env -i ./minishell), sets minimal requirements nodes
**
**     @return Pointer to newly created env list root.
*/
t_env	*init_env(t_minishell *ms, char *av0, char **envp)
{
	int		i;

	ms->env_list = NULL;
	if (envp && envp[0])
	{
		i = 0;
		while (envp[i])
		{
			env_add_back(&ms->env_list, create_node(envp[i]));
			i++;
		}
	}
	if (!_check_env_vars(ms, av0))
		return (NULL);
	return (ms->env_list);
}
