/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 10:33:07 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/23 10:33:28 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

char	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return ('\0');
}

bool	is_quoted_star(char *raw)
{
	return (!ft_strncmp(raw, "'*'", 4) || !ft_strncmp(raw, "\"*\"", 4));
}
