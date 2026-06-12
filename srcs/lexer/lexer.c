/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:23:04 by v                 #+#    #+#             */
/*   Updated: 2026/06/12 11:30:27 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** _extract_word:
**      Increments character pointer until it's space or operator, creates 
**		new token with this content and appends it to tok_list
**
**      @param input  	input string
**      @param ls  		lexer state machine
**      @param tok_ls  	current token
*/
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

/*
** _process_character:
**      Determines what the first character is (quote, operator, word)
** 		and dispatch it accordingly
**
**      @param input  	input string
**      @param ls  		lexer state machine
**      @param tok_ls  	current token
**      @return 		1 if everything works out / 0 if not
*/
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
