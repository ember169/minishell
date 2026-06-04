/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 09:33:20 by alma              #+#    #+#             */
/*   Updated: 2026/06/04 13:58:58 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	exec_subshell(t_minishell *ms, t_ast_node *node)
{
	int status;

	printf("[EXEC] SUBSHELL () - Simulation isolation (futur fork)\n");
	status = exec_ast(ms, node->left);
	printf("[EXEC] SUBSHELL () - Fin de l'isolation\n");
	return (status);
}

static int exec_pipe(t_minishell *ms, t_ast_node *node)
{
	int	status_left;
	int	status_right;

	printf("[EXEC] PIPE (|) - Simulation création du tube\n");
	printf("[EXEC] PIPE (|) - Visite gauche...\n");
	status_left = exec_ast(ms, node->left);
	printf("[EXEC] PIPE (|) - Visite droite...\n");
	status_right = exec_ast(ms, node->right);
	(void)status_left;
	return (status_right);
}

static int	exec_or(t_minishell *ms, t_ast_node *node)
{
	int	status;

	printf("[EXEC] OR (||) - Évaluation gauche...\n");
	status = exec_ast(ms, node->left);
	if (status != 0)
	{
		printf("[EXEC] OR (||) - Échec gauche, évaluation droite...\n");
		status = exec_ast(ms, node->right);
	}
	else
		printf("[EXEC] OR (||) - Succès gauche, on skip la droite.\n");
	return (status);
}

static int exec_and(t_minishell *ms, t_ast_node *node)
{
	int	status;

	printf("[EXEC] AND (&&) - Évaluation gauche...\n");
	status = exec_ast(ms, node->left);
	if (status == 0)
	{
		printf("[EXEC] AND (&&) - Succès gauche, évaluation droite...\n");
		status = exec_ast(ms, node->right);
	}
	else
		printf("[EXEC] AND (&&) - Échec gauche, on skip la droite.\n");
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
