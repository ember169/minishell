/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 23:49:48 by v                 #+#    #+#             */
/*   Updated: 2026/06/05 00:07:35 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	exec_builtin(t_minishell *ms, t_ast_node *node)
{
	char	*cmd;

	if (!node || !node->args || !node->args[0])
		return (0);
	cmd = node->args[0];
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (execute_echo(node->args));
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (execute_cd(ms, node->args));
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (execute_pwd());
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (execute_export(ms, node->args));
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (execute_unset(ms, node->args));
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (execute_env(ms));
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (execute_exit(ms, node->args));
	return (1);
}
