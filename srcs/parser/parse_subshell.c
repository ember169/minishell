/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:12:15 by v                 #+#    #+#             */
/*   Updated: 2026/07/10 18:26:51 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static t_ast_node	*_ast_new_subshell_node(t_ast_node *child)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = child;
	return (node);
}

static t_token	*find_matching_paren(t_token *tok)
{
	int		lvl;
	t_token	*curr;

	lvl = 0;
	curr = tok;
	while (curr)
	{
		if (curr->type == TOK_PAREN_LEFT)
			lvl++;
		else if (curr->type == TOK_PAREN_RIGHT)
			lvl--;
		if (lvl == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_ast_node	*build_subshell(t_token *tok)
{
	t_token		*end;
	t_token		*cu;
	t_ast_node	*node;

	end = find_matching_paren(tok);
	cu = tok;
	while (cu->next != end)
		cu = cu->next;
	cu->next = NULL;
	node = _ast_new_subshell_node(build_ast(tok->next));
	cu = end->next;
	while (cu)
	{
		append_redir(&(node->redirs), red_new(cu->type, cu->next->value));
		cu = cu->next->next;
	}
	return (free(tok), free_tok_ls(&end), node);
}
