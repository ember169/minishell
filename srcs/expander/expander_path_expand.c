/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_path_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 10:34:21 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/10 14:04:33 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

char	**grab_filenames(char *path)
{
	DIR				*d;
	struct dirent	*e;
	char			**files;
	int				i;

	if (!path)
		path = ".";
	files = malloc(sizeof(char *) * (count_dir_entries(path) + 1));
	if (!files)
		return (NULL);
	d = opendir(path);
	if (!d)
		return (free(files), NULL);
	i = 0;
	e = readdir(d);
	while (e)
	{
		if (e->d_name[0] != '.')
			files[i++] = ft_strdup(e->d_name);
		e = readdir(d);
	}
	files[i] = NULL;
	return (closedir(d), files);
}

char	**match_pattern(char **files, char *pattern, char *dir)
{
	char	**matches;
	int		n;
	int		i;
	int		j;

	n = count_matches(files, pattern);
	if (n == 0)
		return (NULL);
	matches = malloc(sizeof(char *) * (n + 1));
	if (!matches)
		return (NULL);
	i = 0;
	j = 0;
	while (files[i])
	{
		if (match_glob(pattern, files[i]) && dir)
			matches[j++] = ft_strjoin(dir, files[i]);
		else if (match_glob(pattern, files[i]))
			matches[j++] = ft_strdup(files[i]);
		i++;
	}
	matches[j] = NULL;
	sort_matches(matches, j);
	return (matches);
}

t_token	*update_token(char **matches, t_token *current)
{
	t_token	*new_tok;
	t_token	*last;
	char	*val;
	int		i;

	free(current->value);
	current->value = ft_strdup(matches[0]);
	last = current;
	i = 1;
	while (matches[i])
	{
		val = ft_strdup(matches[i]);
		if (!val)
			return (last);
		new_tok = token_new(val, TOK_WORD);
		if (!new_tok)
			return (free(val), last);
		new_tok->next = last->next;
		last->next = new_tok;
		last = new_tok;
		i++;
	}
	return (last);
}

t_token	*expand_path(t_token *current)
{
	char		**filenames;
	char		**matches;
	t_token		*result;
	char		*slash;
	char		*dir;

	slash = ft_strrchr(current->value, '/');
	dir = NULL;
	if (slash)
		dir = ft_substr(current->value, 0, slash - current->value + 1);
	filenames = grab_filenames(dir);
	if (!filenames)
		return (free(dir), current);
	if (slash)
		matches = match_pattern(filenames, slash + 1, dir);
	else
		matches = match_pattern(filenames, current->value, NULL);
	free_str_array(filenames);
	free(dir);
	if (!matches)
		return (current);
	result = update_token(matches, current);
	free_str_array(matches);
	return (result);
}
