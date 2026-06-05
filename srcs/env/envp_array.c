/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 01:41:04 by v                 #+#    #+#             */
/*   Updated: 2026/06/05 01:43:55 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	_env_list_size(t_env *env_list)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = env_list;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**generate_envp_array(t_env *env_list)
{
	t_env	*tmp;
	char	**envp;
	char	*tmp_str;
	int		i;

	envp = malloc(sizeof(char *) * (_env_list_size(env_list) + 1));
	if (!envp)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin(tmp_str, tmp->value);
		free(tmp_str);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
