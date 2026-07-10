/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:46:07 by v                 #+#    #+#             */
/*   Updated: 2026/07/10 20:32:59 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	_free_redir_list(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->file)
			free(redirs->file);
		if (redirs->original_file)
			free(redirs->original_file);
		free(redirs);
		redirs = tmp;
	}
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	free_ast(node->subshell_child);
	if (node->type == NODE_CMD || node->type == NODE_SUBSHELL)
		_free_redir_list(node->redirs);
	if (node->type == NODE_CMD)
		free_str_array(node->args);
	free(node);
}
