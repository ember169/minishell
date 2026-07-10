/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:46:07 by v                 #+#    #+#             */
/*   Updated: 2026/07/10 16:38:15 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	_free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file)
		{
			if (ft_strncmp(tmp->file, "/tmp/.ms_heredoc_", 17) == 0)
				unlink(tmp->file);
			free(tmp->file);
		}
		free(tmp);
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
