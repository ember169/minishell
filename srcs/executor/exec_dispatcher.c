/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 11:35:38 by mskn              #+#    #+#             */
/*   Updated: 2026/07/10 19:36:43 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_is_builtin(char *command)
{
	if (!command)
		return (false);
	if ((ft_strlen("echo") == ft_strlen(command)
			&& ft_strncmp("echo", command, ft_strlen("echo")) == 0)
		|| (ft_strlen("exit") == ft_strlen(command)
			&& ft_strncmp("exit", command, ft_strlen("exit")) == 0)
		|| (ft_strlen("env") == ft_strlen(command)
			&& ft_strncmp("env", command, ft_strlen("env")) == 0)
		|| (ft_strlen("cd") == ft_strlen(command)
			&& ft_strncmp("cd", command, ft_strlen("cd")) == 0)
		|| (ft_strlen("pwd") == ft_strlen(command)
			&& ft_strncmp("pwd", command, ft_strlen("pwd")) == 0)
		|| (ft_strlen("export") == ft_strlen(command)
			&& ft_strncmp("export", command, ft_strlen("export")) == 0)
		|| (ft_strlen("unset") == ft_strlen(command)
			&& ft_strncmp("unset", command, ft_strlen("unset")) == 0))
		return (true);
	return (false);
}

static bool	_is_env_unsafe(char *command)
{
	if (!command)
		return (false);
	if ((ft_strlen("exit") == ft_strlen(command)
			&& ft_strncmp("exit", command, ft_strlen("exit")) == 0)
		|| (ft_strlen("cd") == ft_strlen(command)
			&& ft_strncmp("cd", command, ft_strlen("cd")) == 0)
		|| (ft_strlen("export") == ft_strlen(command)
			&& ft_strncmp("export", command, ft_strlen("export")) == 0)
		|| (ft_strlen("unset") == ft_strlen(command)
			&& ft_strncmp("unset", command, ft_strlen("unset")) == 0))
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
static void	execute_child(t_minishell *ms, t_ast_node *node)
{
	char	*cmd_path;

	init_exec_child_signals();
	if (setup_redirections(node) != 0)
		clean_child_and_exit(ms, 1);
	if (!node->args || !node->args[0])
		clean_child_and_exit(ms, 0);
	if (_is_builtin(node->args[0]))
		clean_child_and_exit(ms, exec_builtin(ms, node));
	cmd_path = get_cmd_path(ms, node->args[0]);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		clean_child_and_exit(ms, 127);
	}
	execve(cmd_path, node->args, ms->envp);
	perror("execve");
	clean_child_and_exit(ms, 126);
}

static int	_exec_parent_builtin(t_minishell *ms, t_ast_node *node)
{
	int	status;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(node) == 0)
		status = exec_builtin(ms, node);
	else
		status = 1;
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
	return (status);
}

int	dispatch_cmd(t_minishell *ms, t_ast_node *node)
{
	pid_t	pid;
	int		status;

	if (!ms || !node)
		return (1);
	if (node->args && node->args[0] && _is_env_unsafe(node->args[0]))
		return (_exec_parent_builtin(ms, node));
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		execute_child(ms, node);
	waitpid(pid, &status, 0);
	ms->last_status = handle_child_status(status);
	return (ms->last_status);
}
