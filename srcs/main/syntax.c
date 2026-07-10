/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 02:23:32 by v                 #+#    #+#             */
/*   Updated: 2026/07/10 18:30:40 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.h"

static bool	_check_paren(t_token *curr, int *par_lvl)
{
	if (curr->type == TOK_PAREN_LEFT)
	{
		(*par_lvl)++;
		if (!curr->next)
			return (print_syntax_error(curr), false);
		if (curr->next->type == TOK_PIPE || curr->next->type == TOK_AND
			|| curr->next->type == TOK_OR
			|| curr->next->type == TOK_PAREN_RIGHT)
			return (print_syntax_error(curr->next), false);
	}
	else
	{
		(*par_lvl)--;
		if (*par_lvl < 0)
			return (print_syntax_error(curr), false);
		if (curr->next && (curr->next->type == TOK_WORD
				|| curr->next->type == TOK_PAREN_LEFT))
			return (print_syntax_error(curr->next), false);
	}
	return (true);
}

static bool	_check_operator(t_token *curr)
{
	if (!curr->next)
		return (print_syntax_error(curr), false);
	if (curr->next->type == TOK_PIPE || curr->next->type == TOK_AND
		|| curr->next->type == TOK_OR
		|| curr->next->type == TOK_PAREN_RIGHT)
		return (print_syntax_error(curr->next), false);
	return (true);
}

static bool	_check_redir_syntax(t_token *curr)
{
	if (!curr->next)
		return (print_syntax_error(curr), false);
	if (curr->next->type != TOK_WORD
		&& curr->next->type != TOK_HEREDOC_QUOTED)
		return (print_syntax_error(curr->next), false);
	return (true);
}

bool	check_syntax(t_token *tok)
{
	int	par_lvl;

	par_lvl = 0;
	if (tok && (tok->type == TOK_PIPE || tok->type == TOK_AND
			|| tok->type == TOK_OR))
		return (print_syntax_error(tok), false);
	while (tok)
	{
		if ((tok->type == TOK_PAREN_LEFT || tok->type == TOK_PAREN_RIGHT)
			&& !_check_paren(tok, &par_lvl))
			return (false);
		else if ((tok->type == TOK_PIPE || tok->type == TOK_AND
				|| tok->type == TOK_OR) && !_check_operator(tok))
			return (false);
		else if (is_redir(tok->type) && !_check_redir_syntax(tok))
			return (false);
		tok = tok->next;
	}
	if (par_lvl != 0)
	{
		ft_putstr_fd("minishell: syntax error: unclosed parenthesis\n", 2);
		return (false);
	}
	return (true);
}
