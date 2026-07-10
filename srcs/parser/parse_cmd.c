/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 01:02:51 by v                 #+#    #+#             */
/*   Updated: 2026/07/10 18:25:38 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	_count_args(t_token *tok)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tok;
	while (current)
	{
		if (is_redir(current->type))
			current = current->next;
		else if (current->type == TOK_WORD)
			count++;
		if (current)
			current = current->next;
	}
	return (count);
}

static void	_fill_cmd_args(t_ast_node *cmd, t_token *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (is_redir(tok->type) && tok->next)
		{
			append_redir(&(cmd->redirs), red_new(tok->type, tok->next->value));
			tok = tok->next;
		}
		else if (tok->type == TOK_WORD)
			cmd->args[i++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	cmd->args[i] = NULL;
}

t_ast_node	*parse_cmd(t_token *tok)
{
	t_ast_node	*cmd;

	cmd = ast_new_cmd_node();
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * (_count_args(tok) + 1));
	if (!cmd->args)
		return (free_ast(cmd), NULL);
	_fill_cmd_args(cmd, tok);
	return (free_tok_ls(&tok), cmd);
}
