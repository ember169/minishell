/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 03:26:39 by v                 #+#    #+#             */
/*   Updated: 2026/06/05 03:55:23 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	_exec_left_child(t_minishell *ms, t_ast_node *node, int *pfd)
{
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	close(pfd[1]);
	exit(exec_ast(ms, node->left));
}

static void	_exec_right_child(t_minishell *ms, t_ast_node *node, int *pfd)
{
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	exit(exec_ast(ms, node->right));
}

int	exec_pipe(t_minishell *ms, t_ast_node *node)
{
	int		pfd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pfd) == -1)
		return (1);
	pid_left = fork();
	if (pid_left == 0)
		_exec_left_child(ms, node, pfd);
	pid_right = fork();
	if (pid_right == 0)
		_exec_right_child(ms, node, pfd);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}

