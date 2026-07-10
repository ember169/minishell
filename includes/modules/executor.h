/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 09:29:00 by alma              #+#    #+#             */
/*   Updated: 2026/07/06 02:44:04 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		exec_ast(t_minishell *ms, t_ast_node *node);
int		dispatch_cmd(t_minishell *ms, t_ast_node *node);
int		setup_redirections(t_ast_node *node);
char	*get_cmd_path(t_minishell *ms, char *cmd);
int		exec_builtin(t_minishell *ms, t_ast_node *node);
int		exec_pipe(t_minishell *ms, t_ast_node *node);
void	clean_child_and_exit(t_minishell *ms, int exit_code);\
int		handle_child_status(int status);

#endif
