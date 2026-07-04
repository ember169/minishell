/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 09:33:20 by alma              #+#    #+#             */
/*   Updated: 2026/07/05 00:58:18 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	exec_subshell(t_minishell *ms, t_ast_node *node)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		init_exec_child_signals();
		if (setup_redirections(node) != 0)
			clean_child_and_exit(ms, 1);
		clean_child_and_exit(ms, exec_ast(ms, node->left));
	}
	waitpid(pid, &status, 0);
	return (handle_child_status(status));
}

static int	exec_or(t_minishell *ms, t_ast_node *node)
{
	int	status;

	status = exec_ast(ms, node->left);
	if (status != 0)
		status = exec_ast(ms, node->right);
	return (status);
}

static int	exec_and(t_minishell *ms, t_ast_node *node)
{
	int	status;

	status = exec_ast(ms, node->left);
	if (status == 0)
		status = exec_ast(ms, node->right);
	return (status);
}


int	exec_ast(t_minishell *ms, t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_CMD)
		return (dispatch_cmd(ms, node));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(ms, node));
	else if (node->type == NODE_AND)
		return (exec_and(ms, node));
	else if (node->type == NODE_OR)
		return (exec_or(ms, node));
	else if (node->type == NODE_SUBSHELL)
		return (exec_subshell(ms, node));
	return (1);
}
