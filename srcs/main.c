/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/08 16:16:13 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;
	char		*input_line;

	(void)ac;
	ms = NULL;
	ms = init_ms(ms, av[0], envp);
	if (!ms)
		return (1);
	print_env_list(ms->env_list);
	clean_ms(ms);
	return (0);
	lexer(input_line, ms);
}
