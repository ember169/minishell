/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:00:30 by v                 #+#    #+#             */
/*   Updated: 2026/07/06 06:07:49 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	clean_child_and_exit(t_minishell *ms, int exit_code)
{
	int	fd;

	if (ms)
	{
		if (ms->envp)
			free_str_array(ms->envp);
		if (ms->ast_root)
			free_ast(ms->ast_root);
		clean_ms(ms);
		free(ms);
	}
	fd = 0;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	exit(exit_code);
}

int	handle_child_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (1);
}
