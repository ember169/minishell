/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 12:10:54 by mskn              #+#    #+#             */
/*   Updated: 2026/07/11 04:52:52 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

static bool	_parse_sign(char *str, int *i, int *sign)
{
	*i = 0;
	*sign = 1;
	while (str[*i] == ' ' || (str[*i] >= '\t' && str[*i] <= '\r'))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (!ft_isdigit(str[*i]))
		return (false);
	return (true);
}

static bool	_is_valid_exit(char *str, long long *code)
{
	int					i;
	int					sign;
	unsigned long long	res;

	if (!_parse_sign(str, &i, &sign))
		return (false);
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		if (sign == 1 && res > LLONG_MAX)
			return (false);
		if (sign == -1 && res > LLONG_MAX)
			return (false);
		i++;
	}
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] != '\0')
		return (false);
	*code = (long long)(res * sign);
	return (true);
}

static void	_exit_numeric_error(t_minishell *ms, char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	clean_child_and_exit(ms, 2);
}

int	execute_exit(t_minishell *ms, char **args)
{
	long long	code;
	int			status;

	status = ms->last_status;
	if (!ms->is_child && isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1])
	{
		if (!_is_valid_exit(args[1], &code))
			_exit_numeric_error(ms, args[1]);
		if (args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		status = (int)(code % 256);
	}
	clean_child_and_exit(ms, status);
	return (1);
}
