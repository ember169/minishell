/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:08:28 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/04 15:18:44 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
	Potential performances improvements: 
	- refactor extract_key and extract_value in a single function
	- only one allocation instread of three ?
*/

#include "../../includes/includes.h"

static char	*_extract_key(char *env)
{
	char	*m_key;
	int		i;

	if (!environ)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	m_key = ft_calloc(i + 1, sizeof(char));
	if (!m_key)
		return (m_key);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		m_key[i] = env[i];
		i++;
	}
	return (m_key);
}

static char	*_extract_value(char *env)
{
	char	*m_value;
	int		i;
	int		j;

	if (!environ)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
		i++;
	m_value = ft_calloc(ft_strlen(&env[i]) + 1, sizeof(char));
	if (!m_value)
		return (m_value);
	j = 0;
	while (env[i])
		m_value[j++] = env[i++];
	return (m_value);
}

t_env	*_create_node(char *env)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->key = _extract_key(env);
	printf("key = \"%s\"\n", ret->key);
	ret->value = _extract_value(env);
	printf("value = \"%s\"\n", ret->value);
	return (ret);
}

t_env	*init_env(t_minishell *ms)
{
	t_env	*root;
	t_env	*current;
	t_env	*next;
	int		i;

	root = _create_node(environ[0]);
	current = root;
	i = 1;
	while (environ[i])
	{
		next = _create_node(environ[i]);
		if (!next)
			return (clean_ms(ms), next);
		current->next = next;
		current = current->next;
		i++;
	}
	return (root);
}
