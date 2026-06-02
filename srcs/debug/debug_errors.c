/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:45:29 by mskn              #+#    #+#             */
/*   Updated: 2026/06/02 12:45:43 by mskn             ###   ########.fr       */
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
