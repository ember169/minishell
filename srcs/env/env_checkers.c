/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:29:23 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/10 14:25:00 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	check_env_pwd(t_minishell *ms)
{
	t_env	*target;
	char	*cwd;
	char	*join;

	if (!ms)
		return (-1);
	cwd = getcwd(NULL, 0);
	target = get_env_addr_from_key(ms, "PWD");
	if (!target)
	{
		join = ft_strjoin("PWD=", cwd);
		target = create_node(join);
		if (!target)
			return (free(join), -1);
		env_add_back(&ms->env_list, target);
		free(join);
	}
	else
		put_env_value(target, cwd);
	free(cwd);
	return (1);
}

int	check_env_old_pwd(t_minishell *ms)
{
	t_env	*target;

	if (!ms)
		return (-1);
	target = get_env_addr_from_key(ms, "OLDPWD");
	if (!target)
	{
		target = create_node("OLDPWD=");
		if (!target)
			return (-1);
		env_add_back(&ms->env_list, target);
	}
	return (1);
}

int	check_env_path(t_minishell *ms)
{
	t_env	*target;

	if (!ms)
		return (-1);
	target = get_env_addr_from_key(ms, "PATH");
	if (!target)
	{
		target = \
create_node("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
		if (!target)
			return (-1);
		env_add_back(&ms->env_list, target);
	}
	return (1);
}

int	check_env_underscore(t_minishell *ms, char *av0)
{
	t_env	*target;
	char	*join;

	if (!ms)
		return (-1);
	target = get_env_addr_from_key(ms, "_");
	if (!target)
	{
		join = ft_strjoin("_=", av0);
		target = create_node(join);
		if (!target)
			return (free(join), -1);
		free(join);
		env_add_back(&ms->env_list, target);
	}
	else
		put_env_value(target, av0);
	return (1);
}

int	check_env_shlvl(t_minishell *ms)
{
	t_env	*target;
	int		val;
	char	*new_val;

	if (!ms)
		return (-1);
	target = get_env_addr_from_key(ms, "SHLVL");
	if (!target)
	{
		target = create_node("SHLVL=1");
		env_add_back(&ms->env_list, target);
	}
	else
	{
		val = ft_atoi(target->value);
		if (val < 0)
			val = 0;
		else
			val++;
		new_val = ft_itoa(val);
		put_env_value(target, new_val);
		free(new_val);
	}
	return (1);
}
