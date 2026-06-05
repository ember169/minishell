/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:00:46 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/05 01:06:15 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	_throw_error(void)
{
	perror("minishell: export");
	return (1);
}

static bool	_check_key(char *key)
{
	size_t	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (false);
	i = 0;
	while (ft_isalnum(key[i]) || key[i] == '_')
		i++;
	if (i != ft_strlen(key))
		return (false);
	return (true);
}

static int	_export_one_var(t_minishell *ms, char *arg)
{
	char	*key;
	char	*value;
	t_env	*var;

	key = extract_key(arg);
	if (!_check_key(key))
		return (free(key), 1);
	value = extract_value(arg);
	var = get_env_addr_from_key(ms, key);
	if (var)
	{
		put_env_value(var, value);
		return (free(key), free(value), 0);
	}
	else
	{
		env_add_back(&ms->env_list, create_node(arg));
		return (free(key), free(value), 0);
	}
}

void	_export_list(t_env *root)
{
	t_env	*current;

	current = root;
	while (current)
	{
		write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		ft_printf("%s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}

int	execute_export(t_minishell *ms, char **args)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (!args[i])
		_export_list(ms->env_list);
	else
	{
		while (args[i])
		{
			if (_export_one_var(ms, args[i]) != 0)
			{
				_throw_error();
				ret++;
			}
			i++;
		}
	}
	return (ret);
}
