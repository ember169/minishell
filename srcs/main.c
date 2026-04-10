/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/10 13:28:10 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;
	t_token		*tok_ls;

	(void)ac;
	ms = NULL;
	ms = init_ms(ms, av[0], envp);
	if (!ms)
		return (1);
	//print_env_list(ms->env_list);
	tok_ls = lexer("ls| grep c >out");
	clean_ms(ms);
	free_tok_ls(&tok_ls);
	return (0);
}
