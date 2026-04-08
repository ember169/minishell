/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/08 14:27:48 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	(void)ac;
	ms = NULL;
	ms = init_ms(ms, av[0], envp);
	if (!ms)
		return (1);
	print_env_list(ms->env_list);
	clean_ms(ms);
	return (0);
}
