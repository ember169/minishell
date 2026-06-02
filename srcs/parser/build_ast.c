/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:30:24 by v                 #+#    #+#             */
/*   Updated: 2026/06/02 12:34:21 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static t_ast_node	*_split_ast_op(t_token *tok, t_token *split_pts)
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
	right_ast = build_ast(right_tok);
	if (split_pts->value)
		free(split_pts->value);
	free (split_pts);
	return (ast_new_op(node_type, left_ast, right_ast));
}

static int	_count_args(t_token *tok)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tok;
	while (current)
	{
		if (is_redir(current->type))
			current = current->next;
		else if (current->type == TOK_WORD)
			count++;
		if (current)
			current = current->next;
	}
	return (count);
}

static void	_fill_cmd_args(t_ast_node *cmd, t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (is_redir(tok->type) && tok->next)
		{
			append_redir(&(cmd->redirs), red_new(tok->type, tok->next->value));
			tok = tok->next;
		}
		else if (tok->type == TOK_WORD)
			cmd->args[i++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	cmd->args[i] = NULL;
}

static t_ast_node	*_parse_cmd(t_token *tok)
{
	t_ast_node	*cmd;
	t_token		*head;

	head = tok;
	cmd = ast_new_cmd_node();
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (_count_args(tok) + 1));
	if (!cmd->args)
		return (free_ast(cmd), NULL);
	_fill_cmd_args(cmd, tok);
	free_tok_ls(&head);
	return (cmd);
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
	return (_parse_cmd(tok));
}
