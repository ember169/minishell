/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 14:57:27 by v                 #+#    #+#             */
/*   Updated: 2026/07/05 21:13:00 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

t_ast_node	*build_ast(t_token *tok);
bool		is_redir(t_token_type type);
t_redir		*red_new(t_token_type type, char *file);
void		append_redir(t_redir **redirs, t_redir *new_node);
t_ast_node	*ast_new_cmd_node(void);
t_ast_node	*ast_new_op(t_node_type type, t_ast_node *left, t_ast_node *right);
void		print_ast(t_ast_node *node, int level);
t_token		*find_logical_op(t_token *tok);
t_token		*find_pipe_op(t_token *tok);
void		free_ast(t_ast_node *node);
t_ast_node	*build_subshell(t_token *tok);
int			process_all_heredocs(t_minishell *ms, t_ast_node *node);
void		print_syntax_error(t_token *tok);
t_ast_node	*parse_cmd(t_token *tok);
char		*expand_heredoc_line(t_minishell *ms, char	*line);

#endif
