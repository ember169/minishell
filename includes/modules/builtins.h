/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 14:54:50 by lgervet           #+#    #+#             */
/*   Updated: 2026/06/05 00:07:35 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	execute_echo(char **args);
int	execute_cd(t_minishell *ms, char **args);
int	execute_env(t_minishell *ms);
int	execute_exit(t_minishell *ms, char **args);
int	execute_export(t_minishell *ms, char **args);
int	execute_pwd(void);
int	execute_unset(t_minishell *ms, char **args);

#endif
