/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:25:26 by v                 #+#    #+#             */
/*   Updated: 2026/06/12 11:26:06 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** _append_op:
**      Create a new token, appends it to tok_list, increment character pointer
**
**      @param tok_ls  	token list
**      @param ls  		lexer state machine
**      @param type  	operator type
**      @param size  	number of character to increment pointer
**      @return 		true if success / false
*/
static bool	_append_op(
	t_token **tok_ls,
	t_lexer_state *ls,
	t_token_type type,
	int size)
{
	t_token	*new;

	new = token_new(NULL, type);
	if (!new)
		return (false);
	token_add_back(tok_ls, new);
	ls->i += size;
	return (true);
}

/*
** _handle_double_op:
**      Determines if input[n] and input[n+1] are the same operator. 
**		Appends two of them to tok_list
**
**      @param input 	input string
**      @param ls  		lexer state machine
**      @param tok_ls 	token list
**      @return 		true if success / false
*/
static bool	_handle_double_op(char *input, t_lexer_state *ls, t_token **tok_ls)
{
	if (input[ls->i] == '>' && input[ls->i +1] == '>')
		return (_append_op(tok_ls, ls, TOK_REDIR_APPEND, 2));
	if (input[ls->i] == '<' && input[ls->i +1] == '<')
		return (_append_op(tok_ls, ls, TOK_HEREDOC, 2));
	if (input[ls->i] == '|' && input[ls->i +1] == '|')
		return (_append_op(tok_ls, ls, TOK_OR, 2));
	if (input[ls->i] == '&' && input[ls->i +1] == '&')
		return (_append_op(tok_ls, ls, TOK_AND, 2));
	return (false);
}

/*
** handle_operator:
**      Determines if one or more operators. If one, append according token 
**		to tok_ls. If more, calls _handle_double_op
**
**      @param input 	input string
**      @param ls  		lexer state machine
**      @param tok_ls 	token list
**      @return 		true if success / false
*/
bool	handle_operator(char *input, t_lexer_state *ls, t_token **tok_ls)
{
	if (_handle_double_op(input, ls, tok_ls))
		return (true);
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
	else if (input[ls->i] == '&')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `&'\n", 2);
		return (false);
	}
	return (true);
}

/*
** handle_quotes:
**      Uses state machine to add_back content between quotes as a new token
**
**      @param input  	input string
**      @param ls  		state machine
**      @param tok_ls  	current token
**      @return 		/
*/
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
