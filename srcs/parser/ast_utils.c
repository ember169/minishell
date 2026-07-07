/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 13:49:31 by v                 #+#    #+#             */
/*   Updated: 2026/07/07 01:49:08 by v                ###   ########.fr       */
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

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->subshell_child = NULL;
	node->args = NULL;
	node->redirs = NULL;
	return (node);
}
/*
il serait logique de se demander pourquoi on a deux fonction quasi identiques.
c'est assez simple en faite: c'est l'ordre de prio de l'AST. 
meme si avec du recul une fonction avec un argument en plus marche aussi
c'est cheangable mais osef un peu juste ca a une justification quoi.
*/

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

void	print_syntax_error(t_token *tok)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (tok && tok->value)
		ft_putstr_fd(tok->value, 2);
	else if (tok->type == TOK_PIPE)
		ft_putstr_fd("|", 2);
	else if (tok->type == TOK_AND)
		ft_putstr_fd("&&", 2);
	else if (tok->type == TOK_OR)
		ft_putstr_fd("||", 2);
	else if (tok->type == TOK_PAREN_LEFT)
		ft_putstr_fd("(", 2);
	else if (tok->type == TOK_PAREN_RIGHT)
		ft_putstr_fd(")", 2);
	else if (tok->type == TOK_REDIR_IN)
		ft_putstr_fd("<", 2);
	else if (tok->type == TOK_REDIR_OUT)
		ft_putstr_fd(">", 2);
	else if (tok->type == TOK_REDIR_APPEND)
		ft_putstr_fd(">>", 2);
	else if (tok->type == TOK_HEREDOC || tok->type == TOK_HEREDOC_QUOTED)
		ft_putstr_fd("<<", 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}
