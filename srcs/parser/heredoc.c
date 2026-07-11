/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:09:06 by v                 #+#    #+#             */
/*   Updated: 2026/07/06 00:44:39 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* heredoc.c                                          :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/02 13:09:06 by v                 #+#    #+#             */
/* Updated: 2026/06/27 03:00:00 by v                ###   ########.fr       */
/* */
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

static void	_fill_heredoc(t_minishell *ms, int fd, char *delim, bool expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (expand)
			line = expand_heredoc_line(ms, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
	}
}

static void	_heredoc_child(t_minishell *ms, t_redir *redir, char *file)
{
	int	fd;

	init_exec_child_signals();
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd >= 0)
	{
		_fill_heredoc(ms, fd, redir->file, redir->type == TOK_HEREDOC);
		close (fd);
	}
	free(file);
	clean_ms(ms);
	free(ms);
	exit(0);
}

static int	_process_single_heredoc(t_minishell *ms, t_redir *redir)
{
	pid_t			pid;
	int				status;
	char			*tmp_file;
	struct termios	term;

	tmp_file = _generate_tmp_filename();
	if (isatty(STDIN_FILENO))
		tcgetattr(STDIN_FILENO, &term);
	init_exec_parent_signals();
	pid = fork();
	if (pid == 0)
		_heredoc_child(ms, redir, tmp_file);
	waitpid(pid, &status, 0);
	if (isatty(STDIN_FILENO))
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	init_interactive_signals();
	free(redir->file);
	redir->file = tmp_file;
	redir->type = TOK_REDIR_IN;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (130);
	}
	return (0);
}

int	process_all_heredocs(t_minishell *ms, t_ast_node *node)
{
	t_redir	*curr;

	if (!node)
		return (0);
	if (node->type == NODE_CMD)
	{
		curr = node->redirs;
		while (curr)
		{
			if (curr->type == TOK_HEREDOC || curr->type == TOK_HEREDOC_QUOTED)
			{
				if (_process_single_heredoc(ms, curr) == 130)
					return (130);
			}
			curr = curr->next;
		}
	}
	else
	{
		if (process_all_heredocs(ms, node->left) == 130)
			return (130);
		if (process_all_heredocs(ms, node->right) == 130)
			return (130);
	}
	return (0);
}
