/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:04:24 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/23 10:33:31 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** check_for_var:
**     Recursively checks for $ is in a string (unless escaped by \))
**
**     @param *value  String to check
**     @return Pointer to $ in string if found, NULL if not
*/
char	*check_for_var(char *str)
{
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = ft_strchr(str, '$');
	if (!ptr)
		return (NULL);
	if (ptr > str && *(ptr - 1) == '\\')
		return (check_for_var(ptr + 1));
	return (ptr);
}

/*
** get_key_len:
**     Returns the length of variable key
**
**     @param *dollar_ptr 	Pointer to the dollar in str
**     @return key length
*/
int	get_key_len(char *dollar_ptr)
{
	int	key_len;

	key_len = 1;
	if (dollar_ptr[1] == '?')
		return (key_len);
	while ((dollar_ptr[key_len] && ft_isalnum(dollar_ptr[key_len])) || \
dollar_ptr[key_len] == '_')
		key_len++;
	return (key_len - 1);
}

/*
** get_env_var:
**     Finds according variable value in ms->env_list:
**	   fills *`var with it or with empty string if not found.
**
**     @param *ms		Pointer to minishell super structure
**     @param *dollar	Pointer to string at dollar char
**     @param **var		String in which put the env_list->value
*/
void	get_env_var(t_minishell *ms, char *dollar, char **var)
{
	char		*key;
	int			key_len;
	t_env		*env;

	key_len = get_key_len(dollar);
	key = ft_substr(dollar, 1, key_len);
	if (!key)
	{
		*var = ft_strdup("");
		return ;
	}
	if (key_len == 1 && *key == '?')
		*var = ft_itoa(ms->last_status);
	else
	{
		env = get_env_addr_from_key(ms, key);
		if (!env)
			*var = ft_strdup("");
		else
			*var = ft_strdup(env->value);
	}
	free(key);
}
