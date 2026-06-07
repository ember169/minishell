/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:12:15 by v                 #+#    #+#             */
/*   Updated: 2026/06/07 18:37:58 by v                ###   ########.fr       */
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
	int		lvl = 0;
	t_token	*curr = tok;

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
	t_token		*curr;
	t_ast_node	*node;

	end = find_matching_paren(tok);
	if (!end)
		return (print_syntax_error(NULL), free_tok_ls(&tok), NULL);
	curr = tok;
	while (curr->next != end)
		curr = curr->next;
	curr->next = NULL;
	node = _ast_new_subshell_node(build_ast(tok->next));
	curr = end->next;
	while (curr)
	{
		if (is_redir(curr->type) && curr->next)
		{
			append_redir(&(node->redirs), red_new(curr->type, curr->next->value));
			curr = curr->next->next;
		}
		else
			return (print_syntax_error(curr), free_ast(node), free(tok), free_tok_ls(&end), NULL);
	}
	return (free(tok), free_tok_ls(&end), node);
}

