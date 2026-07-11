/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:20:45 by lgervet           #+#    #+#             */
/*   Updated: 2026/07/11 03:03:17 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

//meaage d'erreur en cas de dossier inexistant

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
static void	_set_env(t_minishell *ms, char *key, char *value)
{
	t_env	*node;
	char	*tmp;
	char	*entry;

	node = get_env_addr_from_key(ms, key);
	if (node)
	{
		put_env_value(node, value);
		return ;
	}
	tmp = ft_strjoin(key, "=");
	entry = ft_strjoin(tmp, value);
	free(tmp);
	env_add_back(&ms->env_list, create_node(entry));
	free(entry);
}

static int	_change_dir(t_minishell *ms, char *dir)
{
	char	*cwd;
	char	*new_cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		if (chdir(dir) == -1)
			free(cwd);
		else
		{
			_set_env(ms, "OLDPWD", cwd);
			free(cwd);
			new_cwd = getcwd(NULL, 0);
			if (!new_cwd)
				return (1);
			_set_env(ms, "PWD", new_cwd);
			free(new_cwd);
			return (0);
		}
	}
	return (1);
}

static int	_throw_error(char *dir)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (!dir)
		perror("");
	else
		perror(dir);
	return (1);
}

static int	_cd_home(t_minishell *ms)
{
	char	*buf;

	buf = get_env_value_from_key(ms, "HOME");
	if (!buf)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (buf[0] == '\0')
		return (0);
	if (_change_dir(ms, buf) > 0)
		return (_throw_error(buf));
	return (0);
}

// First condition:
// 		cd			   → chdir to HOME
// 		cd /nonexistent → print error, return 1
// Second condition:
// 		cd - 			→ chdir to OLDPWD, then print it
// Else:
// 		cd /some/path	→ chdir to the given path	
int	execute_cd(t_minishell *ms, char **args)
{
	char	*buf;

	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!args[1])
		return (_cd_home(ms));
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		buf = get_env_value_from_key(ms, "OLDPWD");
		if (_change_dir(ms, buf) > 0)
			return (_throw_error(buf));
		ft_putstr_fd(get_env_value_from_key(ms, "PWD"), 1);
		ft_putstr_fd("\n", 1);
	}
	else if (_change_dir(ms, args[1]) > 0)
		return (_throw_error(args[1]));
	return (0);
}
