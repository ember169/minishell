/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alma <alma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:52:41 by v                 #+#    #+#             */
/*   Updated: 2026/04/30 14:41:28 by alma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	print_redir(t_redir *redir)
{
	ft_printf("  Redirs: ");
	while (redir)
	{
		if (redir->type == TOK_REDIR_IN)
			ft_printf("< ");
		else if (redir->type == TOK_REDIR_OUT)
			printf("> ");
		else if (redir->type == TOK_REDIR_APPEND)
			printf(">> ");
		else if (redir->type == TOK_HEREDOC)
			printf("<< ");
		ft_printf("'%s'", redir->file);
		redir = redir->next;
	}

}

static void	print_cmd_node(t_ast_node *node)
{
	int		i;
	t_redir	*redir;

	ft_printf("CMD :[");
	i = 0;
	while (node->args && node->args[i])
	{
		ft_printf("'%s'", node->args[i]);
		if (node->args[i + 1])
			ft_printf(", ");
		i++;
	}
	ft_printf("]");
	redir = node->redirs;
	if (redir)
		print_redir(redir);
	printf("\n");
}

void	print_ast(t_ast_node *node, int level)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < level)
	{
		ft_printf("\t");
		i++;
	}
	if (node->type == NODE_PIPE)
		ft_printf("[PIPE |]\n");
	else if (node->type == NODE_AND)
		ft_printf("[AND &&]\n");
	else if (node->type == NODE_OR)
		ft_printf("[OR ||]\n");
	else if (node->type == NODE_SUBSHELL)
		ft_printf("[SUBSHELL ()]\n");
	else if (node->type == NODE_CMD)
		print_cmd_node(node);
	if (node->left)
		print_ast(node->left, level + 1);
	if (node->right)
		print_ast(node->right, level + 1);
}
