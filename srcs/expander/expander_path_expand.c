/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_path_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <lgervet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 10:34:21 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/02 17:39:12 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

// It updates the token list
// returns the pointer to the last inserted token so the expander loop knows 
// where to continue iterating OR NULL if no matches is empty;
t_token	*update_token(char **matches, t_token *current_token)
{
	free(matches);
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
char	**grab_filenames(char *dir)
{
	DIR		*dir_stream;
	int		i;
	char	**ret;

	dir_stream = opendir(dir);
	i = 0;
	while (dir_stream)
	{
		ret[i] = malloc(ft_strlen(dir_stream[i]))
	}
	
	return (ret);
}

// Fills dir string if any
// Fills pattern string and returns it
static char	*_get_pattern_and_dir(char *str, char *wildcard, char **dir)
{
	char	*ret;

	ret = malloc(ft_strlen(wildcard) + 1);
	if (!ret)
		return (NULL);
	if (str != wildcard)
	{
		*dir = malloc((ft_strlen(str) - ft_strlen(wildcard)) + 1);
		if (!(*dir))
			return (NULL);
		ft_strlcpy(*dir, str, ft_strlen(str) - ft_strlen(wildcard));
	}
	while (ret && str && !is_space(*str))
	{
		// if (*str == '*')
		// 	???
		*ret = *str;
		ret++;
		str++;
	}
	*ret = '\0';
	return (ret);
}

t_token	*expand_path_loop(t_minishell *ms, t_token *current)
{
	char	*ptr;
	char	*pattern;
	char	*dir;
	char	**filenames;
	char	**matches;

	ptr = ft_strchr(current->value, '*');
	if (!ptr)
		return (current->next);
	pattern = _get_pattern_and_dir(current->value, ptr, &dir);
	filenames = _grab_filenames(dir);
	matches = match_pattern(filenames, pattern);
	free(pattern);
	free(filenames);
	return (update_token(matches, current));
}
