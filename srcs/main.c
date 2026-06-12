/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/12 11:59:51 by mskn             ###   ########.fr       */
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
			ft_printf("Debug mode ON.\n\n");
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

/*
** _format_tokens:
**      Determines if current token is HEREDOC and next one is quoted
**		to reformat it
**
**      @param *ms  	pointer to t_minishell
**      @param *list  	pointer to token list
**      @return value
*/
// cette fonction devrait s'appeler _manage_heredoc_quotes et l'appel 
// a expand_token_list devrait se faire dans la fonction appelante ??
static void	_format_tokens(t_minishell *ms, t_token *list)
{
	t_token	*tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (tmp->type == TOK_HEREDOC && tmp->next->type == TOK_WORD)
		{
			if (ft_strchr(tmp->next->value, '\'')
				|| ft_strchr(tmp->next->value, '\"'))
				tmp->type = TOK_HEREDOC_QUOTED;
		}
		tmp = tmp->next;
	}
	expand_token_list(ms, list);
	if (ms->debug)
		print_tok_list(list);
}

static int	_process_input(t_minishell *ms, char *uinput)
{
	t_token	*list;

	if (ft_strncmp(uinput, "exit", 5) == 0)
		return (0);
	list = lexer(uinput);
	if (!list)
		return (1);
	_format_tokens(ms, list);
	ms->ast_root = build_ast(list);
	process_all_heredocs(ms, ms->ast_root);
	if (ms->debug)
		print_ast(ms->ast_root, 0);
	if (ms->ast_root)
	{
		ms->envp = generate_envp_array(ms->env_list);
		exec_ast(ms, ms->ast_root);
		free_str_array(ms->envp);
		ms->envp = NULL;
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
			return ;
		if (uinput[0] != '\0')
		{
			add_to_history(uinput);
			_process_input(ms, uinput);
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
