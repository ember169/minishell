/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:57:29 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/23 10:41:56 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static char	*_expand_path(t_minishell *ms, char *str)
{
	if (!ms)
		return ("");
	return (str);
}

/*
** _expand_with_quote:
**		Expands variables with quote management and removal:
**     		- Track quote state (in_quote = '\0' OR '\'' OR '"')
**	   		- Skip expansion when in_quote == '\''
**	  		- Allow expansion when unquoted or in_quote == '"'
**	  		- Strip quotes as it processes
**	  		- Return the final string
**
**     @param param  Description.
**     @return New string.
*/
static char	*_expand_with_quotes(t_minishell *ms, char *str)
{
	char	in_quote;
	char	*ret;
	char	*key;
	char	*var;
	int		i;
	int		j;
	int		key_len;

	in_quote = '\0';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (in_quote == str[i])
			{
				in_quote = '\0';
				i++;
				continue ;
			}
			else if (in_quote == '\0')
			{
				in_quote = str[i];
				i++;
				continue ;
			}
			else
				ret[j++] = str[i++];
		}
		else if (str[i] == '$' && in_quote != '\'')
		{
			key_len = get_key_len(&str[i]);
			if (key_len > 0)
			{
				extract_key(&str[i], &key, key_len);
				get_env_var(ms, &str[i], &var);
				j += append_var(&ret[j], var);
				free(key);
				free(var);
			}
			continue ;
		}
		else
			ret[j++] = str[i++];
	}
	ret[j] = '\0';
	return (ret);
}

/*
** expand_token_list:
**		Iterate through token list, each time a TOK_WORD is encountered:
**			- Variable expansion ($VAR) + quote handling
**			- Pathname expansion (*.txt)
**
**     @param *ms    Pointer to superstructure.
**     @param *head  Head of token chained list.
*/
void	expand_token_list(t_minishell *ms, t_token *head)
{
	t_token	*current;
	char	*expanded;
	char	*expanded_path;

	if (!head || !ms)
		return ;
	current = head;
	while (current)
	{
		if (current->type == TOK_WORD)
		{
			expanded = _expand_with_quotes(ms, current->value);
			free(current->value);
			expanded_path = _expand_path(ms, expanded);
			free(expanded);
			current->value = expanded_path;
		}
		current = current->next;
	}
}
