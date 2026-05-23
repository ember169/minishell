/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:46:07 by v                 #+#    #+#             */
/*   Updated: 2026/05/23 15:35:35 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	free_redir_list(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

static void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free (arr);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	free_ast(node->subshell_child);
	if (node->type == NODE_CMD)
	{
		free_str_array(node->args);
		free_redir_list(node->redirs);
	}
	free (node);
}
