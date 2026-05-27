/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:13:34 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/27 13:07:45 by lgervet          ###   ########.fr       */
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

void	execute_echo(char **args)
{
	bool	has_flag;
	bool	in_flag;
	bool	first_word;
	int		i;

	first_word = true;
	in_flag = true;
	has_flag = false;
	i = 1;
	while (args[i])
	{
		if (!first_word)
			write(STDOUT_FILENO, " ", 1);
		if (!_is_flag(args[i]))
		{
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			first_word = false;
			in_flag = false;
		}
		if (first_word && in_flag)
			has_flag = _is_flag(args[i]);
		i++;
	}
	if (!has_flag)
		write(STDOUT_FILENO, "\n", 1);
}
