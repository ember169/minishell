/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:17:36 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/10 16:08:23 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	_clean_env(t_env *root)
{
	t_env	*current;
	t_env	*next;

	if (!root)
		return ;
	current = root;
	while (current)
	{
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
	return ;
}

static void	_clean_envp(char **envp)
{
	(void)envp;
	return ;
}

static void	_clean_ast(t_ast_node *root)
{
	(void)root;
	return ;
}

void	clean_ms(t_minishell *ms)
{
	int	debug;

	debug = ms->debug;
	if (ms)
	{
		if (ms->env_list)
			_clean_env(ms->env_list);
		if (ms->envp)
			_clean_envp(ms->envp);
		if (ms->ast_root)
			_clean_ast(ms->ast_root);
	}
	free(ms);
	clear_history();
	if (debug)
		printf("Cleanup done ! Terminating.\n");
	return ;
}
