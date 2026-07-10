/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:30:24 by v                 #+#    #+#             */
/*   Updated: 2026/07/10 18:03:16 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static t_node_type	_get_node_type(t_token_type type)
{
	if (type == TOK_PIPE)
		return (NODE_PIPE);
	if (type == TOK_AND)
		return (NODE_AND);
	return (NODE_OR);
}

static t_ast_node	*_handle_split_err(t_ast_node *left, t_ast_node *right)
{
	free_ast(left);
	free_ast(right);
	return (NULL);
}

static t_ast_node	*_split_ast_op(t_token *tok, t_token *split_pts)
{
	t_token		*current;
	t_node_type	type;
	t_ast_node	*left;
	t_ast_node	*right;

	if (tok == split_pts)
		return (print_syntax_error(split_pts), free_tok_ls(&tok), NULL);
	if (!split_pts->next)
		return (print_syntax_error(split_pts), free_tok_ls(&tok), NULL);
	type = _get_node_type(split_pts->type);
	current = tok;
	while (current && current->next != split_pts)
		current = current->next;
	if (current)
		current->next = NULL;
	left = build_ast(tok);
	right = build_ast(split_pts->next);
	if (split_pts->value)
		free(split_pts->value);
	free(split_pts);
	if (!left || !right)
		return (_handle_split_err(left, right));
	return (ast_new_op(type, left, right));
}

t_ast_node	*build_ast(t_token *tok)
{
	t_token	*split_pts;

	if (!tok)
		return (NULL);
	split_pts = find_logical_op(tok);
	if (split_pts)
		return (_split_ast_op(tok, split_pts));
	split_pts = find_pipe_op(tok);
	if (split_pts)
		return (_split_ast_op(tok, split_pts));
	if (tok->type == TOK_PAREN_LEFT)
		return (build_subshell(tok));
	return (parse_cmd(tok));
}
