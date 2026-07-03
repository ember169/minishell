/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 12:10:54 by mskn              #+#    #+#             */
/*   Updated: 2026/07/03 02:31:57 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	_exit_numeric_error(t_minishell *ms, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	clean_ms (ms);
	exit (2);
}

int	execute_exit(t_minishell *ms, char **args)
{
	int	status;

	status = ms->last_status;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1])
	{
		if (!_is_numeric(args[1]))
			_exit_numeric_error(ms, args[1]);
		if (args[2])
		{
			ft_putstr_fd
				("minishell: exit: too many arguments\n", STDERR_FILENO);
			return (1);
		}
		status = ft_atoi(args[1]);
	}
	clean_ms (ms);
	exit (status);
}
