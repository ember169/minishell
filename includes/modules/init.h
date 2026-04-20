/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:51:13 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/18 10:51:14 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

t_minishell	*init_ms(t_minishell *ms, char **av, char **envp);
t_env		*init_env(t_minishell *ms, char *av0, char **envp);
int			check_env_pwd(t_minishell *ms);
int			check_env_old_pwd(t_minishell *ms);
int			check_env_path(t_minishell *ms);
int			check_env_underscore(t_minishell *ms, char *av0);
int			check_env_shlvl(t_minishell *ms);
t_env		*create_node(char *env);
t_env		*get_env_addr_from_key(t_minishell *ms, char *to_find);
t_env		*put_env_value(t_env *env, char *new_value);
void		env_add_back(t_env **root, t_env *new);

#endif