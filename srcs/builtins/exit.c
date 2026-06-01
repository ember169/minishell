/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 12:10:54 by mskn              #+#    #+#             */
/*   Updated: 2026/06/01 12:15:09 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	execute_exit(t_minishell *ms, char **args)
{
	int	last_status;

	(void)args;
	last_status = ms->last_status;
	write(STDERR_FILENO, "exit", ft_strlen("exit"));
	clean_ms(ms);
	exit (last_status);
}
