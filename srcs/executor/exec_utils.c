/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 16:00:30 by v                 #+#    #+#             */
/*   Updated: 2026/07/05 00:55:40 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	clean_child_and_exit(t_minishell *ms, int exit_code)
{
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	close (STDERR_FILENO);

	clean_ms(ms);
	free(ms);
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