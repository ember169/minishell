/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:10:06 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/08 16:12:51 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"


int	_check_debug(char **av)
{
	int	i;
	int	res;

	res = 0;
	i = 1;
	while (av && av[i])
	{
		if (ft_strncmp(av[i], "--debug", 8) == 0)
		{
			printf("Debug mode ON.\n\n");
			res = 1;
			break ;
		}
		i++;
	}
	return (res);
}

t_minishell	*init_ms(t_minishell *ms, char **av, char **envp)
{
	ms = malloc(sizeof(t_minishell));
	if (ms)
	{
		ms->env_list = init_env(ms, av[0], envp);
		ms->envp = NULL;
		ms->last_status = 0;
		ms->ast_root = NULL;
		ms->debug = _check_debug(av);
	}
	return (ms);
}
