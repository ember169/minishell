/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 09:35:47 by mskn              #+#    #+#             */
/*   Updated: 2026/06/01 10:03:45 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

t_env	*create_node(char *env)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->key = extract_key(env);
	ret->value = extract_value(env);
	ret->next = NULL;
	return (ret);
}

static void	_free_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

static t_env	*_find_previous(t_minishell *ms, t_env *node)
{
	t_env	*tmp;
	t_env	*current;

	tmp = NULL;
	current = ms->env_list;
	while (current != node)
	{
		tmp = current;
		current = current->next;
	}
	return (tmp);
}

t_env	*remove_env_node(t_minishell *ms, t_env *node)
{
	t_env	*ret;
	t_env	*prev;

	if (!ms || !node)
		return (NULL);
	if (ms->env_list == node)
	{
		ret = node->next;
		ms->env_list = ret;
		_free_node(node);
	}
	else
	{
		prev = _find_previous(ms, node);
		ret = node->next;
		prev->next = ret;
		_free_node(node);
	}
	return (ret);
}
