/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/20 17:55:27 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static void	_main_loop(t_minishell *ms, t_token *list)
{
	char	*uinput;

	if (!ms)
		return ;
	while (1)
	{
		uinput = readline(PROMPT);
		add_to_history(uinput);
		list = lexer(uinput);
		expand_token_list(ms, list);
		if (ms->debug)
			print_tok_list(list);
		if (ft_strncmp(uinput, "exit", 5) == 0)
			break ;
	}
	free(uinput);
}

static bool	_check_debug(char **av)
{
	int		i;
	bool	res;

	res = false;
	i = 0;
	while (av && av[i])
	{
		if (ft_strncmp(av[i], "--debug", 8) == 0)
		{
			printf("Debug mode ON.\n\n");
			res = true;
			break ;
		}
		i++;
	}
	return (res);
}

static t_minishell	*_init_ms(t_minishell *ms, char **av, char **envp)
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

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;
	t_token		*tok_list;

	(void)ac;
	ms = NULL;
	ms = _init_ms(ms, av, envp);
	if (!ms)
		return (1);
	if (ms->debug)
		print_env_list(ms->env_list);
	tok_list = NULL;
	_main_loop(ms, tok_list);
	free_tok_ls(&tok_list);
	clean_ms(ms);
	free(ms);
	return (0);
}
