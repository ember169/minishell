/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:51:47 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/02 15:04:22 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	print_env_list(t_env *root)
{
	t_env	*current;
	int		i;

	printf("\n========= ENV LIST DEBUG =========\n\n");
	if (!root)
	{
		printf("No env_list found. Exiting\n");
		return ;
	}
	i = 0;
	current = root;
	while (current)
	{
		printf("[%d] \"%s=%s\"\n", i, current->key, current->value);
		i++;
		current = current->next;
	}
	printf("\n\n");
}

void	print_tok_list(t_token *token)
{
	t_token	*current;

	current = token;
	printf("\n========= TOK LIST DEBUG =========\n\n");
	while (current)
	{
		ft_printf("[%d] Value: %s\n", current->type, current->value);
		current = current->next;
	}
	printf("\n\n");
	// current = token;
	// while (current)
	// {
	// 	ft_printf("%s ", current->value);
	// 	current = current->next;
	// }
	// printf("\n\n");
}

static void	_parse_print_ast(t_ast_node *node, int level)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < level)
	{
		printf("\t");
		i++;
	}
	if (node->type == NODE_PIPE)
		printf("[PIPE |]\n");
	else if (node->type == NODE_AND)
		printf("[AND &&]\n");
	else if (node->type == NODE_OR)
		printf("[OR ||]\n");
	else if (node->type == NODE_CMD)
		print_cmd_node(node);
	if (node->left)
		_parse_print_ast(node->left, level + 1);
	if (node->right)
		_parse_print_ast(node->right, level + 1);
}

void	print_ast(t_ast_node *node, int level)
{
	if (!node)
		return ;
	printf("\n========= AST DEBUG =========\n\n");
	_parse_print_ast(node, level);
	printf("\n");
}
