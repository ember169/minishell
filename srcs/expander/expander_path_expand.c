/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_path_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 10:34:21 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/01 13:04:50 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

// It updates the toen list
// returns the pointer to the last inserted token so the expander loop knows 
// where to continue iterating OR NULL if no matches is empty;
t_token	*update_token(char **matches, t_token *current_token)
{
	return (current_token);
}

// It takes the candidate list and the pattern, and returns a filtered list
// of matches
char	**match_pattern(char **filenames, char *pattern)
{
	return (filenames);
}

// It takes the directory path and returns a null-terminated array of strings
// (the filenames found)
char	**grab_filenames(char *path)
{
	return (&path);
}


static void	expand_path(t_minishell *ms, char **src, char **dst)
{
	char	*pattern;
	char	**filenames;
	char	**matches;
	t_token	*current;

	
}

char	*expand_path_loop(t_minishell *ms, t_token *current, char *ret)
{
	char	*src;
	char	*str;
	char	*dst;

	str = current->value;
	src = str;
	dst = ret;
	while (*src)
	{
		if (*src == '*')
			expand_path(ms, &src, &dst);
		else
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
	*dst = '\0';
	return (ret);
}
