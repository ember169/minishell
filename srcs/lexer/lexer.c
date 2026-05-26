/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:23:04 by v                 #+#    #+#             */
/*   Updated: 2026/05/26 09:32:56 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static void	_extract_word(char *input, t_lexer_state *ls, t_token **tok_ls)
{
	int		start;
	char	*word;
	t_token	*new_node;

	start = ls->i;
	while (input[ls->i]
		&& ls->state == GENERAL
		&& !is_space(input[ls->i])
		&& !is_operator(input[ls->i]))
		ls->i++;
	word = ft_substr(input, start, ls->i - start);
	new_node = token_new(word, TOK_WORD);
	if (new_node)
		token_add_back(tok_ls, new_node);
}

static int	_process_character(char *input, t_lexer_state *ls, t_token **tok_ls)
{
	if (input[ls->i] == '\'' || input[ls->i] == '\"')
		handle_quotes(input, ls, tok_ls);
	else if (ls->state == GENERAL && is_space(input[ls->i]))
		ls->i++;
	else if (ls->state == GENERAL
		&& ((input[ls->i] == '&' && input[ls->i + 1] == '&')
			|| (input[ls->i] == '|' && input[ls->i + 1] == '|')
			|| (input[ls->i] == '<' && input[ls->i + 1] == '<')
			|| (input[ls->i] == '>' && input[ls->i + 1] == '>')))
		handle_operator(input, ls, tok_ls);
	else if (ls->state == GENERAL && !is_operator(input[ls->i]))
		_extract_word(input, ls, tok_ls);
	else if (ls->state == GENERAL && is_operator(input[ls->i]))
	{
		if (!handle_operator(input, ls, tok_ls))
			return (0);
	}
	return (1);
}

t_token	*lexer(char *input)
{
	t_lexer_state	ls;
	t_token			*tok_ls;

	tok_ls = NULL;
	ls.state = GENERAL;
	ls.i = 0;
	while (input[ls.i])
	{
		if (!_process_character(input, &ls, &tok_ls))
		{
			free_tok_ls(&tok_ls);
			return (NULL);
		}
	}
	if (ls.state != GENERAL)
	{
		write(2, "error: unclosed quotes\n", 23);
		free_tok_ls(&tok_ls);
		return (NULL);
	}
	return (tok_ls);
}
