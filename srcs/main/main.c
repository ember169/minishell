/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:54:11 by lgervet           #+#    #+#             */
/*   Updated: 2026/07/07 02:40:16 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static void	manage_heredoc_quotes(t_token *list)
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
}

static void	execute_pipeline(t_minishell *ms)
{
	if (ms->debug)
		print_ast(ms->ast_root, 0);
	if (ms->ast_root)
	{
		ms->envp = generate_envp_array(ms->env_list);
		init_exec_parent_signals();
		ms->last_status = exec_ast(ms, ms->ast_root);
		init_interactive_signals();
		free_str_array(ms->envp);
		ms->envp = NULL;
		free_ast(ms->ast_root);
		ms->ast_root = NULL;
	}
}

static int	_process_input(t_minishell *ms, char *uinput)
{
	t_token	*list;

	list = lexer(ms, uinput);
	if (!list)
		return (1);
	if (!check_syntax(list))
	{
		ms->last_status = 2;
		free_tok_ls(&list);
		return (1);
	}
	manage_heredoc_quotes(list);
	expand_token_list(ms, &list);
	if (ms->debug)
		print_tok_list(list);
	ms->ast_root = build_ast(list);
	if (ast_failed(ms, list))
		return (1);
	execute_pipeline(ms);
	return (1);
}

static void	_main_loop(t_minishell *ms)
{
	char	*uinput;

	init_interactive_signals();
	while (1)
	{
		uinput = readline(PROMPT);
		if (!uinput)
			return ;
		if (uinput[0] != '\0')
		{
			add_to_history(uinput);
			if (_process_input(ms, uinput) == 0)
			{
				free(uinput);
				break ;
			}
		}
		free(uinput);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	*ms;
	int			final_status;

	(void)ac;
	ms = NULL;
	ms = init_ms(ms, av, envp);
	if (!ms)
		return (1);
	if (ms->debug)
		print_env_list(ms->env_list);
	_main_loop(ms);
	final_status = ms->last_status;
	clean_ms(ms);
	free(ms);
	return (final_status);
}
