/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:57:29 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/27 17:25:19 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static char	*_expand_with_path(t_minishell *ms, char *str)
{
	if (!ms)
		return ("");
	return (str);
}

/*
** _expand_with_quotes:
**     Allocates expanded string and feeds it to main expander loop
**
**     @param *ms  	Pointer to minishell structure
**     @param *str  String to expand
**     @return expanded string once the expand_loop is done
*/
static char	*_expand_with_quotes(t_minishell *ms, char *str)
{
	int		allocated;
	char	*ret;

	allocated = ft_strlen(str) * 2 + 256;
	ret = malloc(allocated);
	if (!ret)
		return (NULL);
	return (expand_loop(ms, str, ret));
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
			current->value = expanded;
			expanded_path = _expand_with_path(ms, expanded);
			// free(expanded);
			current->value = expanded_path;
		}
		current = current->next;
	}
}
