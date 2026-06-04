/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 09:29:00 by alma              #+#    #+#             */
/*   Updated: 2026/06/04 23:18:13 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int	exec_ast(t_minishell *ms, t_ast_node *node);
int	dispatch_cmd(t_minishell *ms, t_ast_node *node);
int	setup_redirections(t_ast_node *node);
char	*get_cmd_path(t_minishell *ms, char *cmd);

#endif
