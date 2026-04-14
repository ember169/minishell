/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 10:48:03 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/14 18:21:53 by lgervet          ###   ########.fr       */
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
	int	i;

	printf("\n========= TOK LIST DEBUG =========\n\n");
	i = 0;
	while (token)
	{
		ft_printf("[%d] Value: \"%s\" | Type:  [%d]\n", \
i, token->value, token->type);
		token = token->next;
		i++;
	}
	printf("\n\n");
}
