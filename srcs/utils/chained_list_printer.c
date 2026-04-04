/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_printer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 10:48:03 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/04 10:59:31 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	print_env_list(t_env *root)
{
	t_env	*current;
	int		i;

	printf("\n==== ENV LIST DEBUG ====\n");
	i = 0;
	current = root;
	while (current)
	{
		printf("[%d] \"%s=%s\"\n", i, current->key, current->value);
		i++;
		current = current->next;
	}
}
