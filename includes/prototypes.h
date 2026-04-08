/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:37:07 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/08 11:56:50 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* ==== INITIALIZATION ==== */
t_minishell	*init_ms(t_minishell *ms, char *av0);
t_env		*init_env(t_minishell *ms, char *av0);
int			check_env_pwd(t_minishell *ms);
int			check_env_old_pwd(t_minishell *ms);
int			check_env_path(t_minishell *ms);
int			check_env_underscore(t_minishell *ms, char *av0);
int			check_env_shlvl(t_minishell *ms);

/* ==== UTILITIES ==== */
void		print_env_list(t_env *root);
void		clean_ms(t_minishell *ms);
t_env		*create_node(char *env);
t_env		*get_env_addr_from_key(t_minishell *ms, char *to_find);
t_env		*put_env_value(t_env *env, char *new_value);
void		env_add_back(t_env **root, t_env *new);

#endif
