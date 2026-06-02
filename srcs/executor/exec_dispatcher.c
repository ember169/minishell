/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:35:38 by mskn              #+#    #+#             */
/*   Updated: 2026/06/02 20:30:19 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_is_builtin(char *command)
{
	if (!command)
		return (false);
	if (\
(ft_strlen("echo") == ft_strlen(command) && \
ft_strncmp("echo", command, ft_strlen("echo")) == 0) || \
(ft_strlen("exit") == ft_strlen(command) && \
ft_strncmp("exit", command, ft_strlen("exit")) == 0) || \
(ft_strlen("env") == ft_strlen(command) && \
ft_strncmp("env", command, ft_strlen("env")) == 0) || \
(ft_strlen("cd") == ft_strlen(command) && \
ft_strncmp("cd", command, ft_strlen("cd")) == 0) || \
(ft_strlen("pwd") == ft_strlen(command) && \
ft_strncmp("pwd", command, ft_strlen("pwd")) == 0) || \
(ft_strlen("export") == ft_strlen(command) && \
ft_strncmp("export", command, ft_strlen("export")) == 0) || \
(ft_strlen("unset") == ft_strlen(command) && \
ft_strncmp("unset", command, ft_strlen("unset")) == 0))
		return (true);
	return (false);
}

static bool	_is_env_unsafe(char *command)
{
	if (!command)
		return (false);
	if (\
(ft_strlen("exit") == ft_strlen(command) && \
ft_strncmp("exit", command, ft_strlen("exit")) == 0) || \
(ft_strlen("cd") == ft_strlen(command) && \
ft_strncmp("cd", command, ft_strlen("cd")) == 0) || \
(ft_strlen("export") == ft_strlen(command) && \
ft_strncmp("export", command, ft_strlen("export")) == 0) || \
(ft_strlen("unset") == ft_strlen(command) && \
ft_strncmp("unset", command, ft_strlen("unset")) == 0))
		return (true);
	return (false);
}

/*
** dispatch_cmd:
**		1. Takes a command node and check if needs to exec a built-in or not
**			If yes: checks if need to exec in fork or not
**		2. Make it happen.
**
**     @param *ms 	 	Pointer to Minishell superstructure
**     @param *node		Pointer to command node
**     @return 0 on success / >0 on error
*/
int	dispatch_cmd(t_minishell *ms, t_ast_node *node)
{
	if (!ms || !node)
		return (1);
	if (_is_builtin(node->args[0]))
	{
		printf("  -> [CMD] %s is built-in\n", node->args[0]);
		if (_is_env_unsafe(node->args[0]))
		{
			printf("  -> [CMD] %s isn't env safe\n", node->args[0]);
			// Determiner s'ils ont un pipe a droite
			// Si oui : fork()
			// Si non: execution dans le processus parent
		}
		else
		{
			printf("  -> [CMD] %s is env safe\n", node->args[0]);
			// execution dans le processus parent ?
		}

	}
	else
	{
		printf("  -> [CMD] %s is external\n", node->args[0]);
		// Fork it
		// waitpid()
		// Update ms->last_status
	}
	return (0);
}
