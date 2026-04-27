/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:25:26 by v                 #+#    #+#             */
/*   Updated: 2026/04/27 17:22:28 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	_append_op(
	t_token **tok_ls,
	t_lexer_state *ls,
	t_token_type type,
	int size)
{
	t_token	*new;

	new = token_new(NULL, type);
	if (!new)
		return (0);
	token_add_back(tok_ls, new);
	ls->i += size;
	return (1);
}

static int	_handle_double_op(char *input, t_lexer_state *ls, t_token **tok_ls)
{
	if (input[ls->i] == '>' && input[ls->i +1] == '>')
		return (_append_op(tok_ls, ls, TOK_REDIR_APPEND, 2));
	if (input[ls->i] == '<' && input[ls->i +1] == '<')
		return (_append_op(tok_ls, ls, TOK_HEREDOC, 2));
	if (input[ls->i] == '|' && input[ls->i +1] == '|')
		return (_append_op(tok_ls, ls, TOK_OR, 2));
	if (input[ls->i] == '&' && input[ls->i +1] == '&')
		return (_append_op(tok_ls, ls, TOK_AND, 2));
	return (0);
}

void	handle_quotes(char *input, t_lexer_state *ls, t_token **tok_ls)
{
	int		start;
	char	*word;
	char	quote_char;
	t_token	*new_node;

	start = ls->i;
	quote_char = input[ls->i];
	if (quote_char == '\'' || quote_char == '\"')
		ls->state = IN_QUOTE;
	ls->i++;
	while (input[ls->i] && input[ls->i] != quote_char)
		ls->i++;
	if (input[ls->i] == quote_char)
	{
		ls->state = GENERAL;
		ls->i++;
	}
	word = ft_substr(input, start, ls->i - start);
	new_node = token_new(word, TOK_WORD);
	if (new_node)
		token_add_back(tok_ls, new_node);
}

void	handle_operator(char *input, t_lexer_state *ls, t_token **tok_ls)
{
	if (_handle_double_op(input, ls, tok_ls))
		return ;
	if (input[ls->i] == '>')
		_append_op(tok_ls, ls, TOK_REDIR_OUT, 1);
	else if (input[ls->i] == '<')
		_append_op(tok_ls, ls, TOK_REDIR_IN, 1);
	else if (input[ls->i] == '|')
		_append_op(tok_ls, ls, TOK_PIPE, 1);
	else if (input[ls->i] == '(')
		_append_op(tok_ls, ls, TOK_PAREN_LEFT, 1);
	else if (input[ls->i] == ')')
		_append_op(tok_ls, ls, TOK_PAREN_RIGHT, 1);
}
