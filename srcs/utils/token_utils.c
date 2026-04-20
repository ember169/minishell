/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:10:40 by v                 #+#    #+#             */
/*   Updated: 2026/04/20 13:10:49 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	token_add_back(t_token **root, t_token *new)
{
	t_token	*tmp;

	if (!root || !new)
		return ;
	if (!*root)
	{
		*root = new;
		return ;
	}
	tmp = *root;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*token_new(char *value, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

void	free_tok_ls(t_token **tok_ls)
{
	t_token	*tmp;

	if (!tok_ls || !*tok_ls)
		return ;
	while (*tok_ls)
	{
		tmp = *tok_ls;
		*tok_ls = (*tok_ls)->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
