/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast_print_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:52:41 by v                 #+#    #+#             */
/*   Updated: 2026/06/04 23:32:29 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	_print_redir(t_redir *redir)
{
	printf("  Redirs: ");
	while (redir)
	{
		if (redir->type == TOK_REDIR_IN)
			printf("< ");
		else if (redir->type == TOK_REDIR_OUT)
			ft_printf("> ");
		else if (redir->type == TOK_REDIR_APPEND)
			ft_printf(">> ");
		else if (redir->type == TOK_HEREDOC)
			printf("<< ");
		printf("'%s'", redir->file);
		redir = redir->next;
	}
}

void	print_cmd_node(t_ast_node *node)
{
	int		i;
	t_redir	*redir;

	printf("CMD :[");
	i = 0;
	while (node->args && node->args[i])
	{
		printf("'%s'", node->args[i]);
		if (node->args[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
	redir = node->redirs;
	if (redir)
		_print_redir(redir);
	printf("\n");
}
