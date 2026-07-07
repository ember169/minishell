/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:12:15 by v                 #+#    #+#             */
/*   Updated: 2026/07/07 04:56:46 by v                ###   ########.fr       */
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

static t_ast_node	*_subshell_err(
	t_ast_node *n, t_token *t, t_token *end, t_token *err)
{
	print_syntax_error(err);
	free_ast(n);
	free(t);
	free_tok_ls(&end);
	return (NULL);
}

t_ast_node	*build_subshell(t_token *tok)
{
	t_token		*end;
	t_token		*cu;
	t_ast_node	*node;

	end = find_matching_paren(tok);
	if (!end)
		return (print_syntax_error(NULL), free_tok_ls(&tok), NULL);
	cu = tok;
	while (cu->next != end)
		cu = cu->next;
	cu->next = NULL;
	node = _ast_new_subshell_node(build_ast(tok->next));
	cu = end->next;
	while (cu)
	{
		if (!is_redir(cu->type) || !cu->next || cu->next->type != TOK_WORD)
		{
			if (is_redir(cu->type))
				cu = cu->next;
			return (_subshell_err(node, tok, end, cu));
		}
		append_redir(&(node->redirs), red_new(cu->type, cu->next->value));
		cu = cu->next->next;
	}
	return (free(tok), free_tok_ls(&end), node);
}
