/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/27 13:21:52 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

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

static int	_process_input(t_minishell *ms, char *uinput)
{
	t_token	*list;

	if (ft_strncmp(uinput, "exit", 5) == 0)
		return (0);
	list = lexer(uinput);
	if (!list)
		return (1);
	expand_token_list(ms, list);
	if (ms->debug)
		print_tok_list(list);
	ms->ast_root = build_ast(list);
	if (ms->debug)
		print_ast(ms->ast_root, 0);
	if (ms->ast_root)
	{
		free_ast(ms->ast_root);
		ms->ast_root = NULL;
	}
	return (1);
}

static void	_main_loop(t_minishell *ms)
{
	char	*uinput;

	while (1)
	{
		uinput = readline(PROMPT);
		if (!uinput)
			break ;
		if (uinput[0] != '\0')
			add_to_history(uinput);
		if (!_process_input(ms, uinput))
		{
			free(uinput);
			break ;
		}
		free(uinput);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;

	(void)ac;
	ms = NULL;
	ms = _init_ms(ms, av, envp);
	if (!ms)
		return (1);
	if (ms->debug)
		print_env_list(ms->env_list);
	_main_loop(ms);
	clean_ms(ms);
	free(ms);
	return (0);
}
