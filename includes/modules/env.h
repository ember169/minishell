/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:51:13 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/05 01:43:46 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

t_env		*init_env(t_minishell *ms, char *av0, char **envp);
int			check_env_pwd(t_minishell *ms);
int			check_env_old_pwd(t_minishell *ms);
int			check_env_path(t_minishell *ms);
int			check_env_underscore(t_minishell *ms, char *av0);
int			check_env_shlvl(t_minishell *ms);
t_env		*create_node(char *env);
int			remove_env_node(t_minishell *ms, t_env *node);
char		*extract_value(char *env);
char		*extract_key(char *env);
t_env		*get_env_addr_from_key(t_minishell *ms, char *to_find);
char		*get_env_value_from_key(t_minishell *ms, char *key);
t_env		*put_env_value(t_env *env, char *new_value);
void		env_add_back(t_env **root, t_env *new);
char	    **generate_envp_array(t_env *env_list);

#endif
