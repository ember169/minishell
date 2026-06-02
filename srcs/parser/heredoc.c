/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:09:06 by v                 #+#    #+#             */
/*   Updated: 2026/06/02 14:30:14 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static char	*_generate_tmp_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*filename;

	num = ft_itoa(i++);
	filename = ft_strjoin("/tmp/.ms_heredoc_", num);
	free(num);
	return (filename);
}

static void	_fill_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line | ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
	}
}

static void	_process_single_heredoc(t_minishell *ms, t_redir *redir)
{
	int		fd;
	char	*tmp_file;

	tmp_file = _generate_tmp_filename();
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC | 0644);
	if (fd < 0)
	{
		free(tmp_file);
		return ;
	}
	_fill_heredoc(fd, redir->file);
	close(fd);
	free(redir->file);
	redir->file = tmp_file;
	redir->type = TOK_REDIR_IN;
}

void	process_all_heredocs(t_minishell *ms, t_ast_node *node)
{
	t_redir	*current_redir;

	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		current_redir = node->redirs;
		while (current_redir)
		{
			if (current_redir->type == TOK_HEREDOC)
				_process_single_heredoc(ms, current_redir);
			current_redir = current_redir->next;
		}
	}
	else
	{
		process_all_heredocs(ms, node->left);
		process_all_heredocs(ms, node->right);
	}
}
