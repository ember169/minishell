/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alma <alma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:49:31 by v                 #+#    #+#             */
/*   Updated: 2026/04/30 16:00:49 by alma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

t_ast_node	*ast_new_cmd_node(void)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->left = NULL;
	node->right = NULL;
	node->subshell_child = NULL;
	node->args = NULL;
	node->redirs = NULL;
	return (node);
}

t_ast_node	*ast_new_op(t_node_type type, t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}

t_token	*find_logical_op(t_token *tok)
{
	t_token	*current;
	t_token	*last_found;
	int		par_lvl;

	current = tok;
	last_found = NULL;
	par_lvl = 0;
	while (current)
	{
		if (current->type == TOK_PAREN_LEFT)
			par_lvl++;
		else if (current->type == TOK_PAREN_RIGHT)
			par_lvl--;
		else if (par_lvl == 0
			&& (current->type == TOK_AND || current->type == TOK_OR))
			last_found = current;
		current = current->next;
	}
	return (last_found);
}

t_token	*find_pipe_op(t_token *tok)
{
	t_token	*current;
	t_token	*last_found;
	int		par_lvl;

	current = tok;
	last_found = NULL;
	par_lvl = 0;
	while (current)
	{
		if (current->type == TOK_PAREN_LEFT)
			par_lvl++;
		else if (current->type == TOK_PAREN_RIGHT)
			par_lvl--;
		else if (par_lvl == 0 && current->type == TOK_PIPE)
			last_found = current;
		current = current->next;
	}
	return (last_found);
}
