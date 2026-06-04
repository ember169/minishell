/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:36:19 by v                 #+#    #+#             */
/*   Updated: 2026/06/04 20:22:23 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

bool	is_redir(t_token_type type) // a proto
{
	if (type == TOK_REDIR_IN
		|| type == TOK_REDIR_OUT
		|| type == TOK_REDIR_APPEND
		|| type == TOK_HEREDOC
		|| type == TOK_HEREDOC_QUOTED)
		return (true);
	return (false);
}

t_redir	*red_new(t_token_type type, char *file)
{
	t_redir	*new_node;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->file = ft_strdup(file);
	new_node->next = NULL;
	return (new_node);
}

void	append_redir(t_redir **redirs, t_redir *new_node)
{
	t_redir	*tmp;

	if (!redirs || !new_node)
		return ;
	if (!*redirs)
	{
		*redirs = new_node;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
