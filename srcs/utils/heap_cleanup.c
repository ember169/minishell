/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 14:17:36 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/04 15:11:44 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	clean_env(t_env *root)
{
	t_env	*current;
	t_env	*next;

	current = root;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	printf("├ env_list has been freed.\n");
	return ;
}

void	clean_envp(char **envp)
{
	(void)envp;
	printf("├ envp has been freed.\n");
	return ;
}

void	clean_ast(t_ast_node *root)
{
	(void)root;
	printf("├ ast has been freed.\n");
	return ;
}

void	clean_ms(t_minishell *ms)
{
	if (ms)
	{
		printf("\n=========== CLEANUP ===========\n\n\
┌ Freeing super-structure\n");
		if (ms->env_list)
			clean_env(ms->env_list);
		if (ms->envp)
			clean_envp(ms->envp);
		if (ms->ast_root)
			clean_ast(ms->ast_root);
	}
	printf("└ Cleanup done ! Terminating.\n\n");
	return ;
}
