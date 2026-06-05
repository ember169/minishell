/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 10:27:37 by mskn              #+#    #+#             */
/*   Updated: 2026/05/30 10:32:25 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	execute_env(t_minishell *ms)
{
	t_env	*current;

	if (!ms || !ms->env_list)
		return (1);
	current = ms->env_list;
	while (current)
	{
		if (current->value)
			ft_printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
