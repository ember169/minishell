/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:08:28 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/04 11:48:38 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/* ==== GLOBAL VAR ==== */
extern char	**environ;

/* ==== TODO ==== */
//	- Allocate only once per t_env (currently three per t_env)
//	- Create cleanup functions
//	- Free entire list and children when error when creating node

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

t_env	*init_env(void)
{
	t_env	*root;
	t_env	*current;
	int		i;

	root = _create_node(environ[0]);
	current = root;
	i = 1;
	while (environ[i])
	{
		current->next = _create_node(environ[i]);
		current = current->next;
		i++;
	}
	return (root);
}
