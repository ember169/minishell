/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:04:24 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/20 10:50:44 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

/*
** check_for_var:
**     Recursively checks for $ is in a string (unless escaped by \))
**
**     @param *value  String to check
**     @return Pointer to $ in string if found, NULL if not
*/
char	*check_for_var(char *str)
{
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = ft_strchr(str, '$');
	if (!ptr)
		return (NULL);
	if (ptr > str && *(ptr - 1) == '\\')
		return (check_for_var(ptr + 1));
	return (ptr);
}

/*
** get_key_len:
**     Returns the length of variable key
**
**     @param *dollar_ptr 	Pointer to the dollar in str
**     @return key length
*/
int	get_key_len(char *dollar_ptr)
{
	int	key_len;

	key_len = 1;
	if (dollar_ptr[1] == '?')
		return (key_len);
	while ((dollar_ptr[key_len] && ft_isalnum(dollar_ptr[key_len])) || \
dollar_ptr[key_len] == '_')
		key_len++;
	return (key_len - 1);
}
