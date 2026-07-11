/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:57:29 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/27 03:03:10 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

t_token	*expand_with_path(t_token *current)
{
	if (!ft_strchr(current->value, '*'))
		return (current);
	return (expand_path(current));
}

static void	_update_quote(char *in_quotes, char c)
{
	if (*in_quotes == c)
		*in_quotes = '\0';
	else if (*in_quotes == '\0')
		*in_quotes = c;
}

static int	_calc_len(t_minishell *ms, char *str)
{
	int		len;
	char	in_quotes;
	char	*var;

	len = 0;
	in_quotes = '\0';
	while (*str)
	{
		if (is_quote(*str) && (in_quotes == *str || in_quotes == '\0'))
			_update_quote(&in_quotes, *str++);
		else if (*str == '$' && in_quotes != '\'' && get_key_len(str) > 0)
		{
			get_env_var(ms, str, &var);
			len += ft_strlen(var);
			str += (1 + get_key_len(str));
			free (var);
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len + 1);
}

/*
** _expand_with_quotes:
**     Allocates expanded string and feeds it to main expander loop
**
**     @param *ms  	Pointer to minishell structure
**     @param *str  String to expand
**     @return expanded string once the expand_loop is done
*/
char	*expand_with_quotes(t_minishell *ms, char *str)
{
	char	*ret;

	if (!ms)
		return (NULL);
	ret = malloc(_calc_len(ms, str));
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
void	expand_token_list(t_minishell *ms, t_token **head)
{
	t_token	*current;
	t_token	*prev;
	bool	is_delim;
	bool	was_heredoc;

	if (!head || !*head || !ms)
		return ;
	current = *head;
	prev = NULL;
	is_delim = false;
	while (current)
	{
		was_heredoc = (current->type == TOK_HEREDOC
				|| current->type == TOK_HEREDOC_QUOTED);
		if (current->type == TOK_WORD && is_delim)
			strip_delim_quotes(current->value);
		if (current->type == TOK_WORD && !is_delim)
			current = expand_one_word(ms, head, &prev, current);
		else
		{
			prev = current;
			current = current->next;
		}
		is_delim = was_heredoc;
	}
}
