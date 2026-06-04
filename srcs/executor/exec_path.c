/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 22:59:45 by v                 #+#    #+#             */
/*   Updated: 2026/06/04 23:21:51 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static char	**_get_env_path(t_minishell *ms)
{
	t_env	*path_node;

	path_node = get_env_addr_from_key(ms, "PATH");
	if (!path_node || !path_node->value)
		return (NULL);
	return (ft_split(path_node->value, ':'));
}

char	*get_cmd_path(t_minishell *ms, char *cmd)
{
	char	**paths;
	char	*tmp;
	char	*full_path;
	int		i;

	if (cmd && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = _get_env_path(ms);
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_str_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_str_array(paths);
	return (NULL);
}
