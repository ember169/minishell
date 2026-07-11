/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:51:23 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/23 18:34:05 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

t_token		*lexer(t_minishell *ms, char *input);
bool		handle_operator(char *input, t_lexer_state *ls, t_token **tok_ls);
void		handle_quotes(char *input, t_lexer_state *ls, t_token **tok_ls);
int			is_space(char c);
int			is_operator(char c);
void		free_tok_ls(t_token **tok_ls);
void		print_tok_list(t_token *token);
void		token_add_back(t_token **root, t_token *new);
t_token		*token_new(char *value, t_token_type type);

#endif
