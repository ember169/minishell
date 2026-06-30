/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 20:05:39 by alma              #+#    #+#             */
/*   Updated: 2026/06/30 17:41:59 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static int	_calc_heredoc_len(t_minishell *ms, char *line)
{
	int		len;
	char	*val;

	len = 0;
	while (*line)
	{
		if (*line == '$' && get_key_len(line) > 0)
		{
			get_env_var(ms, line, &val);
			len += ft_strlen(val);
			line += (1 + get_key_len(line));
			free (val);
		}
		else
		{
			len++;
			line++;
		}
	}
	return (len + 1);
}

static void	_copy_expanded_var(t_minishell *ms, char **src, char **dst)
{
	char	*val;
	int		len;

	get_env_var(ms, *src, &val);
	len = ft_strlen(val);
	ft_memcpy(*dst, val, len);
	*dst += len;
	*src += (1 + get_key_len(*src));
	free (val);
}

char	*expand_heredoc_line(t_minishell *ms, char	*line)
{
	char	*ret;
	char	*src;
	char	*dst;

	ret = malloc(_calc_heredoc_len(ms, line));
	if (!ret)
		return (line);
	src = line;
	dst = ret;
	while (*src)
	{
		if (*src == '$' && get_key_len(src) > 0)
			_copy_expanded_var(ms, &src, &dst);
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (free(line), ret);
}
