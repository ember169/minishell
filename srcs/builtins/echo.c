/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:13:34 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/26 15:27:03 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_is_flag(char *arg)
{
	if (arg[0] == '-' && arg[1] == 'n' && arg[2] == '\0')
		return (true);
	return (false);
}

static bool	_has_flag(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (_is_flag(args[i]))
			return (true);
		i++;
	}
	return (false);
}

/*
** execute_echo:
**     Implementation of standard echo behavior
**
**     @param **args  Array of strings sent by executor (args[0] == "echo")
**     @return Valeur retour.
*/
void	execute_echo(char **args)
{
	bool	flag;
	bool	first;
	int		i;

	flag = _has_flag(args);
	first = true;
	i = 1;
	while (args[i])
	{
		if (!_is_flag(args[i]))
		{
			if (!first)
				write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			first = false;
		}
		i++;
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	return ;
}
