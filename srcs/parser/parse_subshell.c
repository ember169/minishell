/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:12:15 by v                 #+#    #+#             */
/*   Updated: 2026/05/23 16:35:53 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"


static t_ast_node	*ast_new_subshell_node(t_ast_node *child)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = child;
	return (node);
}

bool	is_fully_enclosed(t_token *tok)
{
	int		par_lvl;
	t_token	*curr;

	if (!tok || tok->type != TOK_PAREN_LEFT)
		return (false);
	par_lvl = 0;
	curr = tok;
	while (curr)
	{
		if (curr->type == TOK_PAREN_LEFT)
			par_lvl++;
		else if (curr->type == TOK_PAREN_RIGHT)
			par_lvl--;
		if (par_lvl == 0 && curr->next != NULL)
			return (false);
		curr = curr->next;
	}
	return (par_lvl == 0);
}

t_ast_node	*build_subshell(t_token *tok)
{
	t_token		*inner_start;
	t_token		*curr;
	t_token		*end_paren;
	t_ast_node	*node;

	inner_start = tok->next;
	if (inner_start->type == TOK_PAREN_RIGHT)
		return (NULL);
	curr = inner_start;
	while (curr->next->type != TOK_PAREN_RIGHT || curr->next->next != NULL)
		curr = curr->next;
	end_paren = curr->next;
	curr->next = NULL;
	node = ast_new_subshell_node(build_ast(inner_start));
	free(tok);
	free(end_paren);
	return (node);
}

