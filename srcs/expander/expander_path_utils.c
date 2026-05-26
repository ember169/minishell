/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_path_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:00:00 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/23 18:14:29 by v                ###   ########.fr       */
=======
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:00:00 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/10 12:06:26 by lgervet          ###   ########.fr       */
>>>>>>> 43aa03f5e0750a31ffc3e8b015a6a1190450b0e7
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

// "Glob" is the Unix term for filename pattern matching with wildcards
/*
** match_glob:
**     Recursively decides if a filename matches a given glob pattern
**
**     @param *pattern 	 Glob pattern to check for
**     @param *str		 String (filename) to check
**     @return true / false
*/
bool	match_glob(char *pattern, char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (true);
		while (*str)
		{
			if (match_glob(pattern, str))
				return (true);
			str++;
		}
		return (false);
	}
	if (*pattern == *str)
		return (match_glob(pattern + 1, str + 1));
	return (false);
}

/*
** sort_matches:
**     Bubble sort matches in alphabetical order in order to respect
**	   POSIX behavior
**
**     @param **arr  Array of string to sort
**     @param n  	 Number of strings to sort
*/
void	sort_matches(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1],
					ft_strlen(arr[j]) + 1) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	count_dir_entries(char *path)
{
	DIR				*d;
	struct dirent	*e;
	int				count;

	d = opendir(path);
	if (!d)
		return (0);
	count = 0;
	e = readdir(d);
	while (e)
	{
		if (e->d_name[0] != '.')
			count++;
		e = readdir(d);
	}
	return (closedir(d), count);
}

int	count_matches(char **filenames, char *pattern)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (filenames[i])
	{
		if (match_glob(pattern, filenames[i]))
			count++;
		i++;
	}
	return (count);
}

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
