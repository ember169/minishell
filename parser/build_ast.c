/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:30:24 by v                 #+#    #+#             */
/*   Updated: 2026/04/15 18:02:58 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static t_token	*find_logical_op(t_token *tok)
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
}

static t_ast_node	*split_ast_op(t_token *tok, t_token *split_pts)
{
	t_token		*current;
	t_token		*right_tok;
	t_node_type	node_type;
	t_ast_node	*left_ast;
	t_ast_node	*right_ast;

	if (split_pts->type == TOK_PIPE)
		node_type = NODE_PIPE;
	else if (split_pts->type == TOK_AND)
		node_type = NODE_AND;
	else
		node_type = NODE_OR;
	right_tok = split_pts->next;
	current = tok;
	while (current && current->next != split_pts)
		current = current->next;
	if (current)
		current->next = NULL;
	left_ast = build_ast(tok);
	right_ast = buil_ast(right_tok);
	free (split_pts);
	return (ast_new_op(node_type, left_ast, right_ast));
}

static int	count_args(t_token *tok)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tok;
	while (current)
	{
		if (current->type == TOK_REDIR_IN
			|| current->type == TOK_REDIR_OUT
			|| current->type == TOK_REDIR_APPEND
			|| current->type == TOK_HEREDOC)
			current = current->next;
		else if (current->type == TOK_WORD)
			count++;
		if (current)
			current = current->next;
	}
	return (count);
}

static t_ast_node	*parse_cmd(t_token *tok)
{
	t_ast_node	*cmd_node;
	t_token		*current;
	int			i;

	cmd_node = ast_new_cmd_node();
	if (!cmd_node)
		return (NULL);
	cmd_node->args = malloc(sizeof(char*) * (count_args(tok) + 1));
	if (!cmd_node->args)
		return (NULL);
	current = tok;
	i = 0;
	while (current)
	{
		if (current->type == TOK_REDIR_IN //TODO faire une fonction pour les is_redir 
			|| current->type == TOK_REDIR_OUT
			|| current->type == TOK_REDIR_APPEND
			|| current->type == TOK_HEREDOC)
		{
			// TODO : Créer un t_redir et l'ajouter à cmd_node->redirs
			// append_redir(&(cmd_node->redirs), curr->type, curr->next->value);
			current = current->next;
		}
		else if (current->type == TOK_WORD)
		{
			cmd_node->args[i] = ft_strdup(current->value);
			if (!cmd_node->args[i])
				return (NULL);
			i++;
		}
		current = current->next;
	}
	cmd_node->args[i] = NULL;
	return (cmd_node);
}

t_ast_node	*build_ast(t_token *tok) // a proto
{
	t_token	*split_pts;

	if (!tok)
		return (NULL);
	split_pts = find_logical_op(tok);
	if (split_pts)
		return (split_ast_op(tok, split_pts));
	split_pts = find_pipe_op(tok);
	if (split_pts)
		return (split_ast_op(tok, split_pts));
	return (parse_cmd(tok));
}
