/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:33:07 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/27 14:03:22 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** _in_quote_switcher:
**     State machine for quote handling. Updates quote state and advances
**     input pointer. Does not write to output when entering/exiting quotes.
**
**     @param *in_quote  Pointer to current quote state
**     @param **src      Pointer to current input character
**     @param **dst      Pointer to current output character
*/
static void	_in_quote_switcher(char *in_quote, char **src, char **dst)
{
	if (*in_quote == **src)
	{
		*in_quote = '\0';
		(*src)++;
	}
	else if (*in_quote == '\0')
	{
		*in_quote = **src;
		(*src)++;
	}
	else
	{
		**dst = **src;
		(*dst)++;
		(*src)++;
	}
}

/*
** _expand_one_var:
**     Expands a variable starting at src. Extracts variable name, looks up
**     value in environment, and appends it to dst. Advances src past variable.
**
**     @param *ms   Pointer to minishell structure
**     @param **src Pointer to $ character
**     @param **dst Pointer to output buffer position
*/
static void	_expand_one_var(t_minishell *ms, char **src, char **dst)
{
	int		key_len;
	char	*key;
	char	*var;

	key_len = get_key_len(*src);
	if (key_len <= 0)
	{
		**dst = **src;
		(*dst)++;
		(*src)++;
		return ;
	}
	extract_key(*src, &key, key_len);
	get_env_var(ms, *src, &var);
	append_var(dst, var);
	*src += (1 + key_len);
	free(key);
	free(var);
}

/*
** expand_loop:
**     Main expansion loop. Processes input character by character while
**     tracking quote state. Expands variables, removes quotes, copies chars.
**
**     @param *ms  Pointer to minishell structure
**     @param *str Input string to expand
**     @param *ret Output buffer (pre-allocated)
**     @return Pointer to expanded string
*/
char	*expand_loop(t_minishell *ms, char *str, char *ret)
{
	char	in_quote;
	char	*src;
	char	*dst;

	src = str;
	dst = ret;
	in_quote = '\0';
	while (*src)
	{
		if (is_quote(*src))
			_in_quote_switcher(&in_quote, &src, &dst);
		else if (*src == '$' && in_quote != '\'')
			_expand_one_var(ms, &src, &dst);
		else
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
	*dst = '\0';
	return (ret);
}
