/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 11:06:27 by mskn              #+#    #+#             */
/*   Updated: 2026/06/01 12:00:51 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	execute_unset(t_minishell *ms, char **args)
{
	t_env	*node;
	int		i;
	int		count;

	if (!ms)
		return (1);
	i = 1;
	count = 0;
	while (args[i])
	{
		node = get_env_addr_from_key(ms, args[i]);
		if (remove_env_node(ms, node) != 0)
			count++;
		i++;
	}
	return (count);
}
