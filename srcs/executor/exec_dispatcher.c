/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:35:38 by mskn              #+#    #+#             */
/*   Updated: 2026/06/04 14:46:37 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_is_env_safe(char *command)
{
	int			i;
	size_t		c_len;
	size_t		b_len;
	const char	*builtins[5];

	builtins[0] = "exit";
	builtins[1] = "cd";
	builtins[2] = "export";
	builtins[3] = "unset";
	builtins[4] = NULL;
	i = 0;
	c_len = ft_strlen(command);
	while (builtins[i])
	{
		b_len = ft_strlen(builtins[i]);
		if (b_len == c_len && ft_strncmp(command, builtins[i], c_len) == 0)
			return (false);
		i++;
	}
	return (true);
}

// Note: fork() returns a value which is different in parent process 
// and child process which can be used to differentiate the work of 
// parent and child processes accordingly
// int	execute_cmd_in_fork(t_minishell *ms, t_ast_node *node)
// {
// 	int		status;
// 	pid_t	pid;

// 	status = -1;
// 	pid = fork();
// 	if (pid == 0)
// 		status = execute_cmd(ms, node);
// 	else if (pid > 0)
// 		waitpid(pid, 0, NULL);
// 	return (status);
// }

// int	execute_cmd(t_minishell *ms, t_ast_node *node)
// {
// 	int		status;
// 	char	*path;
// 	char	**envp;

// 	// Build {path}
// 	// Ensure node->args ends with \0
// 	// Build envp
// 	status = execve(path, node->args, envp);
// 	return (status);
// }

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
	printf("-> [CMD] Simulation exécution de : %s\n", node->args[0]);
	status = 1;
	if (_is_env_safe(node->args[0]))
	{
		printf("  -> [CMD] %s is env safe\n", node->args[0]);
		status = execute_cmd_in_fork(ms, node);
	}
	else if (node->right != NULL && node->right->type != NODE_PIPE)
	{
		printf("  -> [CMD] %s is env unsafe\n", node->args[0]);
		status = execute_cmd(ms, node);
	}
	else
		???;
	ms->last_status = status;
	return (status);
}
