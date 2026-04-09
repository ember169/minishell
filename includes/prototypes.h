/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:37:07 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/09 14:02:29 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* ==== INITIALIZATION ==== */
t_minishell	*init_ms(t_minishell *ms, char *av0, char **envp);
t_env		*init_env(t_minishell *ms, char *av0, char **envp);
int			check_env_pwd(t_minishell *ms);
int			check_env_old_pwd(t_minishell *ms);
int			check_env_path(t_minishell *ms);
int			check_env_underscore(t_minishell *ms, char *av0);
int			check_env_shlvl(t_minishell *ms);

/* ==== LEXER ==== */
t_token		*lexer(char *input, t_minishell *ms);
void		handle_operator(char *input, t_lexer_state *ls, t_token **tok_ls);
int			handle_double_op(char *input, t_lexer_state *ls, t_token **tok_ls);
void		handle_quotes(char *input, t_lexer_state *ls, t_token **tok_ls);
void		extract_word(char *input, t_lexer_state *ls, t_token **tok_ls);
int			append_op(
				t_token **tok_ls, t_lexer_state *ls, t_token_type type, int size
				);
void		process_character(
				char *input, t_lexer_state *ls, t_token **tok_ls
				);

/* ==== UTILITIES ==== */
void		print_env_list(t_env *root);
void		clean_ms(t_minishell *ms);
t_env		*create_node(char *env);
t_env		*get_env_addr_from_key(t_minishell *ms, char *to_find);
t_env		*put_env_value(t_env *env, char *new_value);
void		env_add_back(t_env **root, t_env *new);
void		token_add_back(t_token **root, t_token *new);
t_token		*token_new(char *value, t_token_type type);
int			is_space(char c);
int			is_operator(char c);
void	free_tok_ls(t_token **tok_ls);

#endif
