/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leo_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:25:13 by mskn              #+#    #+#             */
/*   Updated: 2026/06/01 16:56:52 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

// returns 0 if built-in, >0 if external
static int	_is_cmd_external(char *command)
{
	return (\
ft_strncmp("echo", command, ft_strlen("echo")) || \
ft_strncmp("exit", command, ft_strlen("exit")) || \
ft_strncmp("env", command, ft_strlen("env")) || \
ft_strncmp("cd", command, ft_strlen("cd")) || \
ft_strncmp("pwd", command, ft_strlen("pwd")) || \
ft_strncmp("export", command, ft_strlen("export")) || \
ft_strncmp("unset", command, ft_strlen("unset")));
}

// returns 0 if does not modify environment, >0 if does
static int	_is_cmd_env_safe(char *command)
{
	return (\
ft_strncmp("exit", command, ft_strlen("exit")) || \
ft_strncmp("cd", command, ft_strlen("cd")) || \
ft_strncmp("export", command, ft_strlen("export")) || \
ft_strncmp("unset", command, ft_strlen("unset")));
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
	if (is_cmd_external(node->args[0]))
	{
		printf("  -> [CMD] %s is external\n", node->args[0]);
		// Fork it
		// waitpid()
		// Update ms->last_status
	}
	else
	{
		printf("  -> [CMD] %s is internal\n", node->args[0]);
		if (_is_cmd_env_safe(node->args[0]))
		{
			printf("  -> [CMD] %s is env safe\n", node->args[0]);
			// ??
		}
		else
		{
			printf("  -> [CMD] %s isn't env safe\n", node->args[0]);
			// ??
		}
	}
	return (0);
}
