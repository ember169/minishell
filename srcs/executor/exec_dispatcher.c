/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:35:38 by mskn              #+#    #+#             */
/*   Updated: 2026/06/04 23:21:50 by v                ###   ########.fr       */
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
int	dispatch_cmd05(t_minishell *ms, t_ast_node *node)
{

	if (!ms || !node)
		return (1);
	if (_is_builtin(node->args[0]))
	{
		printf("  -> [CMD] %s is built-in\n", node->args[0]);
		if (_is_env_unsafe(node->args[0]))
		{
			printf("  -> [CMD] %s isn't env safe\n", node->args[0]);
			// ??
		}
		else
		{
			printf("  -> [CMD] %s is env safe\n", node->args[0]);
			// ??
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
static void	execute_child(t_minishell *ms, t_ast_node *node)
{
	char	*cmd_path;

	if (setup_redirections(node) != 0)
		exit(1);
	if (!node->args || node->args[0])
		exit(0);
	if (_is_builtin(node->args[0]))
	{
		
	}
}

int	dispatch_cmd(t_minishell *ms, t_ast_node *node)
{
	pid_t	pid;
	int		status;

	if (!ms || !node)
		return (1);

	if (_is_env_unsafe(node->args[0]))
	{
		printf("-> [CMD] %s is env unsafe (NO FORK)\n", node->args[0]);
		// Note : Comme on ne fork pas, il faudra plus tard sauvegarder 
		// les STDIN/STDOUT avec dup() avant de lancer setup_redirections,
		// puis les restaurer. Mais la logique de base est là.
	}
	printf("  -> [CMD] %s is env safe or external (FORKING)\n", node->args[0]);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0) // c'est le gosse
	{
		if (setup_redirections(node) != 0)
			exit(1);
		if (_is_builtin(node->args[0]))
		{
			// exec de builtin
			exit(0);
		}
		else
		{
			// char *path = find_cmd_path(...);
			// execve(path, node->args, ms->envp);
			printf("Simulation execve de %s\n", node->args[0]);
			exit(0); // apparament a gerer avec la gestion d'erreur de execve
		}
	}
	else // les parents
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

}
