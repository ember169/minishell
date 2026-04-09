/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:15:01 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/09 10:49:49 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** wrong_usage_message:
**     Function that could be used when user inputs a wrong flag
**
**     @param has_error  Boolean to return
**     @return has_error
*/
int	wrong_usage_message(int has_error)
{
	ft_putendl_fd("Usage: ./minishell [Options]\n\
OPTIONS:\n\
	--debug: Increase verbosity level with debug messages\n\
EXAMPLE:\n\
	./minishell --debug\n", 2);
	return (has_error);
}
