/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:49:50 by lgervet           #+#    #+#             */
/*   Updated: 2026/07/07 01:39:12 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** get_env_from_key:
**     Iterates through t_env chained list to find the node with the
**     corresponding key.
**
**     @param *ms   Pointer to Minishell super structure.
**     @param *key  String to find
**     @return      Pointer to corresponding t_env / NULL if not found
*/
t_env	*get_env_addr_from_key(t_minishell *ms, char *to_find)
{
	t_env	*current;
	size_t	len;

	if (!ms || !ms->env_list || !to_find)
		return (NULL);
	len = ft_strlen(to_find);
	current = ms->env_list;
	while (current)
	{
		if (ft_strncmp(current->key, to_find, len + 1) == 0
			&& current->key[len] == '\0')
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*
** get_env_value_from_key:
**     Gets t_env address and returns a pointer to its value
**
**     @param *ms   Pointer to Minishell super structure.
**     @param *key  Node to get value from
**     @return      Pointer to t_env->value / NULL if not found
*/
char	*get_env_value_from_key(t_minishell *ms, char *key)
{
	t_env	*addr;

	if (!ms || !ms->env_list || !key)
		return (NULL);
	addr = get_env_addr_from_key(ms, key);
	if (!addr)
		return (NULL);
	return (addr->value);
}

/*
** env_add_back:
**     Appends a node at the end of the env_list
**
**     @param **root  Adress of the list's *root
**     @param *new    Pointer to the node to append
*/
void	env_add_back(t_env **root, t_env *new)
{
	t_env	*tmp;

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

/*
** put_env_value:
**     Changes given node's value field content
**
**     @param *env  	  Pointer to t_env node to modify.
**     @param *new_value  String to put.
**     @return 			  Pointer to changed t_env node.
**
**	   Note: alloc a tmp before freeing old env->value to ensure having a value
**	   even if error occurs. It may prevent future segfaults.
*/
t_env	*put_env_value(t_env *env, char *new_value)
{
	char	*tmp;

	if (!new_value)
		new_value = "";
	tmp = ft_strdup(new_value);
	if (!tmp)
		return (NULL);
	free(env->value);
	env->value = tmp;
	return (env);
}
