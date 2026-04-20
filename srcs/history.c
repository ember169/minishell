/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:29:40 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/20 18:02:12 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static bool	_is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

/*
** add_to_history:
**     Checks if passed str in empty or only spaces, if not add_history
**
**     @param *str  user input
*/
void	add_to_history(char *str)
{
	if (!str || _is_only_spaces(str))
		return ;
	add_history(str);
	return ;
}
