/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:13:34 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/30 10:52:57 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_is_flag(char *arg)
{
	int	i;

	i = 2;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

// Sidenote: we could check write return values 
// to return (>0) in case of error, but overkill (?)
int	execute_echo(char **args)
{
	bool	has_flag;
	bool	in_flags;
	int		i;

	in_flags = true;
	has_flag = false;
	i = 1;
	while (args[i])
	{
		if (!in_flags)
			write(STDOUT_FILENO, " ", 1);
		if (!_is_flag(args[i]))
		{
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			in_flags = false;
		}
		if (in_flags)
			has_flag = _is_flag(args[i]);
		i++;
	}
	if (!has_flag)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
