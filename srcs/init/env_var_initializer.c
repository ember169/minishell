/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_initializer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:29:23 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/07 11:19:07 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	_init_pwd(t_minishell *ms)
{
	t_env	*target;
	char	*cwd;

	(void)ms;
	target = get_env_addr_from_key(ms, "PWD");
	cwd = getcwd(NULL, 0);
	put_env_value(target, cwd);
	free(cwd);
	printf("├ ✓ PWD: %s\n", target->value);
	return (1);
}

static int	_init_old_pwd(t_minishell *ms)
{
	t_env	*target;

	target = get_env_addr_from_key(ms, "OLDPWD");
	if (!target)
	{
		target = get_env_addr_from_key(ms, "PWD");
		insert_env_value(target, target->next, "PWD", NULL);
	}
	printf("├ ✓ OLDPWD: %s\n", target->value);
	return (1);
}

static int	_init_path(t_minishell *ms)
{
	t_env	*target;

	(void)ms;
	return (1);
}

static int	_init_underscore(t_minishell *ms)
{
	(void)ms;
	return (1);
}

int	init_env_vars(t_minishell *ms)
{
	printf("\n\n========= ENV VARS INIT DEBUG =========\n\n┌ Initializing:\n");
	if (!_init_pwd(ms))
		return (-1);
	if (!_init_old_pwd(ms))
		return (-1);
	if (!_init_path(ms))
		return (-1);
	if (!_init_underscore(ms))
		return (-1);
	printf("└ Env vars init done !");
	return (1);
}
