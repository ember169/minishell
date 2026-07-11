/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 04:00:00 by lgervet           #+#    #+#             */
/*   Updated: 2026/07/11 04:00:00 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** had_quote:
**     Checks whether a raw (pre-expansion) token value contained any
**     quote character.
**
**     @param *raw  Raw token value
**     @return true if any quote char is present, false otherwise
*/
bool	had_quote(char *raw)
{
	while (*raw)
	{
		if (is_quote(*raw))
			return (true);
		raw++;
	}
	return (false);
}

/*
** drop_token:
**     Unlinks and frees a token from the list, updating *head if it
**     was the first token.
**
**     @param **head    Address of the list's head
**     @param *prev     Node before current (NULL if current is head)
**     @param *current  Node to drop
**     @return          Node that followed the dropped one
*/
t_token	*drop_token(t_token **head, t_token *prev, t_token *current)
{
	t_token	*next;

	next = current->next;
	if (prev)
		prev->next = next;
	else
		*head = next;
	free(current->value);
	free(current);
	return (next);
}

/*
** expand_one_word:
**     Expands a single TOK_WORD token: variable + quote expansion,
**     then pathname expansion, dropping the token entirely if it was
**     unquoted and expanded to an empty string.
**
**     @param *ms      Pointer to minishell superstructure
**     @param **head   Address of the list's head
**     @param **prev   Address of the caller's "previous node" tracker
**     @param *current Token being expanded
**     @return         Next token the caller should process
*/
t_token	*expand_one_word(t_minishell *ms, t_token **head,
		t_token **prev, t_token *current)
{
	char	*expanded;
	bool	no_glob;
	bool	quoted;

	no_glob = is_quoted_star(current->value);
	quoted = had_quote(current->value);
	expanded = expand_with_quotes(ms, current->value);
	free(current->value);
	current->value = expanded;
	if (!quoted && expanded[0] == '\0')
		return (drop_token(head, *prev, current));
	if (!no_glob)
		current = expand_with_path(current);
	*prev = current;
	return (current->next);
}
