/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/10 15:28:51 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	main_loop(t_minishell *ms)
{
	char	*uinput;

	if (!ms)
		return ;
	while (1)
	{
		uinput = readline(PROMPT);
		add_to_history(uinput);
		if (ft_strncmp(uinput, "exit", 5) == 0)
			break ;
	}
	free(uinput);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	(void)ac;
	ms = NULL;
	ms = init_ms(ms, av, envp);
	if (!ms)
		return (1);
	main_loop(ms);
	if (ms->debug)
		print_env_list(ms->env_list);
	clean_ms(ms);
	return (0);
}
