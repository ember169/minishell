/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/14 18:24:23 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

void	main_loop(t_minishell *ms, t_token *list)
{
	char	*uinput;

	if (!ms)
		return ;
	while (1)
	{
		uinput = readline(PROMPT);
		add_to_history(uinput);
		list = lexer(uinput);
		if (ms->debug)
			print_tok_list(list);
		if (ft_strncmp(uinput, "exit", 5) == 0)
			break ;
	}
	free(uinput);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;
	t_token		*tok_list;

	(void)ac;
	ms = NULL;
	ms = init_ms(ms, av, envp);
	if (!ms)
		return (1);
	if (ms->debug)
		print_env_list(ms->env_list);
	tok_list = NULL;
	main_loop(ms, tok_list);
	free_tok_ls(&tok_list);
	clean_ms(ms);
	free(ms);
	return (0);
}
