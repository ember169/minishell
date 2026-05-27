/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:23:29 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/27 15:07:59 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	execute_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		write(STDOUT_FILENO, buf, strlen(buf));
		write(STDOUT_FILENO, "\n", 1);
		free(buf);
		return (0);
	}
	else
	{
		perror("minishell: pwd");
		return (1);
	}
}
