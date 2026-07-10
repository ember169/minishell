/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:06:27 by mskn              #+#    #+#             */
/*   Updated: 2026/07/06 05:01:28 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_check_unset_key(char *key)
{
	size_t	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (false);
	i = 0;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static void	_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

int	execute_unset(t_minishell *ms, char **args)
{
	t_env	*node;
	int		i;
	int		ret;

	if (!ms)
		return (1);
	i = 1;
	ret = 0;
	while (args[i])
	{
		if (!_check_unset_key(args[i]))
		{
			_unset_error(args[i]);
			ret = 1;
		}
		else
		{
			node = get_env_addr_from_key(ms, args[i]);
			remove_env_node(ms, node);
		}
		i++;
	}
	return (ret);
}
