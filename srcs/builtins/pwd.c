/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:23:29 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/30 10:53:33 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	execute_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (buf)
	{
		write(STDOUT_FILENO, buf, ft_strlen(buf));
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
