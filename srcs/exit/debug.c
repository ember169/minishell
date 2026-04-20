/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:51:47 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/20 17:52:26 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

void	print_env_list(t_env *root)
{
	t_env	*current;
	int		i;

	printf("\n========= ENV LIST DEBUG =========\n\n");
	if (!root)
	{
		printf("No env_list found. Exiting\n");
		return ;
	}
	i = 0;
	current = root;
	while (current)
	{
		printf("[%d] \"%s=%s\"\n", i, current->key, current->value);
		i++;
		current = current->next;
	}
	printf("\n\n");
}

void	print_tok_list(t_token *token)
{
	int	i;

	printf("\n========= TOK LIST DEBUG =========\n\n");
	i = 0;
	while (token)
	{
		ft_printf("[%d] Value: \"%s\" | Type:  [%d]\n", \
i, token->value, token->type);
		token = token->next;
		i++;
	}
	printf("\n\n");
}

/*
** wrong_usage_message:
**     Function that could be used when user inputs a wrong flag
**
**     @param has_error  Boolean to return
**     @return has_error
*/
int	wrong_usage_message(int has_error)
{
	ft_putendl_fd("Usage: ./minishell [Options]\n\
OPTIONS:\n\
	--debug: Increase verbosity level with debug messages\n\
EXAMPLE:\n\
	./minishell --debug\n", 2);
	return (has_error);
}
