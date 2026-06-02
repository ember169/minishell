/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 02:15:46 by v                 #+#    #+#             */
/*   Updated: 2026/06/02 03:11:48 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	apply_single_redir(t_redir *redir)
{
	int	fd;
	int	target_fd;

	if (redir->type == TOK_REDIR_IN)
	{
		fd = open(redir->file, O_RDONLY);
		target_fd = STDIN_FILENO;
	}
	else
	{
		if (redir->type == TOK_REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		target_fd = STDOUT_FILENO;
	}
	if (fd < 0)
	{
		perror(redir->file);
		return (1);
	}
	dup2(fd, target_fd);
	close(fd);
	return (0);
}

int	setup_redirections(t_ast_node *node)
{
	t_redir	*current;

	if (!node || !node->redirs)
		return (0);
	current = node->redirs;
	while (current)
	{
		if (current->type != TOK_HEREDOC)
		{
			if (apply_single_redir(current) != 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
