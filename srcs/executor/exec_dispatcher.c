/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:35:38 by mskn              #+#    #+#             */
/*   Updated: 2026/06/03 16:32:03 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_is_env_safe(char *command)
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
		return (false);
	return (true);
}

int	execute_cmd_in_fork(t_minishell *ms, t_ast_node *node)
{
	int		ret;
	pid_t	pid;

	pid = fork();

	waitpid(pid);
	return (ret);
}

int	execute_cmd(t_minishell *ms, t_ast_node *node)
{
	pid_t	pid;
	int		ret;

	// Execute command with execve()
	pid = execve();

	waitpid(pid);
	return (ret);
}

/*
** dispatch_cmd:
**		1. Takes a command node and check if needs to exec a built-in or not
**			If yes: checks if need to exec in fork or not
**		2. Make it happen.
**		3. Updates last_status
**
**     @param *ms 	 	Pointer to Minishell superstructure
**     @param *node		Pointer to command node
**     @return 0 on success / >0 on error
*/
int	dispatch_cmd(t_minishell *ms, t_ast_node *node)
{
	int	status;

	if (!ms || !node)
		return (1);
	if (!_is_env_safe(node->args[0]) && node->right->type != NODE_PIPE)
	{
		printf("  -> [CMD] %s is env unsafe\n", node->args[0]);
		status = execute_cmd(ms, node);
	}
	else
	{
		printf("  -> [CMD] %s is env safe\n", node->args[0]);
		status = execute_cmd_in_fork(ms, node);
	}
	ms->last_status = status;
	return (status);
}
