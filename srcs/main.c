/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/04 14:44:56 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	main(int ac, char **av)
{
	t_minishell	*ms;

	(void)ac;
	(void)av;
	ms = NULL;
	ms = init_ms(ms);
	if (!ms)
		return (1);
	print_env_list(ms->env_list);
	clean_ms(ms);
	return (0);
}
