/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/10 16:13:19 by lgervet          ###   ########.fr       */
=======
/*   Updated: 2026/04/10 13:28:10 by v                ###   ########.fr       */
>>>>>>> phase1_alma
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
	t_token		*tok_ls;

	(void)ac;
	ms = NULL;
	ms = init_ms(ms, av, envp);
	if (!ms)
		return (1);
	main_loop(ms);
	if (ms->debug)
		print_env_list(ms->env_list);
	clean_ms(ms);
	free(ms);
	tok_ls = lexer("ls| grep c >out");
	free_tok_ls(&tok_ls);
	return (0);
}
