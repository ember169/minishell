/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:20:45 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/27 19:03:11 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** _change_dir:
**      1. Get current working directory (cwd),
**		2. Change cwd to asked one,
**		3. Change OLDPWD env value with cwd,
**		4. Get new cwd
**		5. Change PWD env value with new cwd
**
**     @param *ms  t_minishell superstructure
**     @return 0 if success, 1 if error
*/
static int	_change_dir(t_minishell *ms, char *dir)
{
	t_env	*old;
	t_env	*new;	
	char	*cwd;
	char	*new_cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		if (chdir(dir) == -1)
			free(cwd);
		else
		{
			old = get_env_addr_from_key(ms, "OLDPWD");
			put_env_value(old, cwd);
			free(cwd);
			new = get_env_addr_from_key(ms, "PWD");
			new_cwd = getcwd(NULL, 0);
			if (!new_cwd)
				return (1);
			put_env_value(new, new_cwd);
			free(new_cwd);
			return (0);
		}
	}
	return (1);
}

int	execute_cd(t_minishell *ms, char **args)
{
	char	*home;

	// cd			   → chdir to HOME
	// cd /nonexistent → print error, return 1
	if (!args[1])
	{
		home = get_env_value_from_key(ms, "HOME");
		if (!home || _change_dir(ms, home) > 0)
		{
			perror("minishell: cd");
			return (1);
		}
	}
	// cd - 			→ chdir to OLDPWD, then print it
	// cd /some/path	→ chdir to the given path
	else
	{
		
	}
	return (0);
}
