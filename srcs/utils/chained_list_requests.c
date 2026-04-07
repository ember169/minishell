/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_requests.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:41:15 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/07 11:21:35 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** get_env_from_key:
**     Iterates through t_env chained list to find the node with the
**     corresponding key.
**
**     @param *ms   Pointer to Minishell super structure.
**     @param *key  Character array to find
**     @return      Pointer to corresponding t_env / NULL if not found
*/
t_env	*get_env_addr_from_key(t_minishell *ms, char *to_find)
{
	t_env	*current;
	int		i;
	int		len;

	len = (int)ft_strlen(to_find);
	current = ms->env_list;
	while (current->next)
	{
		i = 0;
		while (to_find[i] && current->key[i] == to_find[i])
			i++;
		if (i == len)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*
** insert_env_value:
**     Inserts a new node (N) inbetween others
**
**     @param *previous  Pointer to the N-1 node
**     @param *next      Pointer to the N+1 node
**     @param *key       String to be added as the new node's key
**     @param *value     String to be added as the new node's value
**     @return 			 Pointer to the new created node / NULL.
*/
t_env	*insert_env_value(t_env *previous, t_env *next, char *key, char *value)
{

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
