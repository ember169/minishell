/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:57:29 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/20 13:59:45 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** _reconstruct_str:
**     Merges every str into one, frees the others
**
**     @param *prefix	Prefix string.
**     @param *suffix	Suffix string.
**     @param *var		Var string.
**     @param *ret		Merged string.
*/
static void	_reconstruct_str(char *prefix, char *suffix, char *var, char **ret)
{
	char	*tmp;

	if (!prefix || !suffix || !var)
		return ;
	tmp = ft_strjoin(prefix, var);
	if (!tmp)
		return ;
	*ret = ft_strjoin(tmp, suffix);
	free(tmp);
	free(prefix);
	free(suffix);
	free(var);
}

/*
** _get_env_var:
**     Finds according variable value in ms->env_list:
**	   fills *`var with it or with empty string if not found.
**
**     @param *ms		Pointer to minishell super structure
**     @param *dollar	Pointer to string at dollar char
**     @param **var		String in which put the env_list->value
*/
static void	_get_env_var(t_minishell *ms, char *dollar, char **var)
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

/*
** _isolate_var:
**     Takes everything before and after $VAR in a string to fill buffers
**
**     @param *str		String to treat.
**     @param *dollar	Pointer to dollar char in *str.
**     @param *prefix	String to fill w/ prefix.
**     @param *suffix	String to fill w/ suffix.
*/
static void	_isolate_var(char *str, char *dollar, char **prefix, char **suffix)
{
	int		prefix_len;
	int		key_len;

	prefix_len = dollar - str;
	*prefix = ft_substr(str, 0, prefix_len);
	key_len = get_key_len(dollar);
	*suffix = ft_strdup(dollar + 1 + key_len);
}

/*
** _expand_loop:
**     Recursively :
**		- Checks if var in string, if not return a new allocated str, else:
**		- Asks for isolation of three str parts (before $ | VAR | after $ )
**		- Asks for environment variable
**		- Asks for string construction
**		- Checks again if other variable in str
**
**     @param *ms   Pointer to minishell parent structure
**     @param *str  Pointer to string to check
**     @return Newly allocated char in any case
*/
static char	*_expand_loop(t_minishell *ms, char *str)
{
	char	*prefix;
	char	*var;
	char	*suffix;
	char	*res;
	char	*dollar;

	if (!ms || !str)
		return (NULL);
	res = NULL;
	dollar = check_for_var(str);
	if (!dollar)
		return (ft_strdup(str));
	if (get_key_len(dollar) == 0)
		return (ft_strdup(str));
	_isolate_var(str, dollar, &prefix, &suffix);
	_get_env_var(ms, dollar, &var);
	_reconstruct_str(prefix, suffix, var, &res);
	if (res && check_for_var(res))
	{
		dollar = _expand_loop(ms, res);
		free(res);
		return (dollar);
	}
	return (res);
}

void	expand_token_list(t_minishell *ms, t_token *head)
{
	t_token	*current;
	char	*expanded;

	if (!head || !ms)
		return ;
	current = head;
	while (current)
	{
		if (current->type == TOK_WORD)
		{
			expanded = _expand_loop(ms, current->value);
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
	return ;
}
