/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:10:06 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/04 14:33:44 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

// typedef struct s_minishell
// {
// 	t_env		*env_list;		// Pointeur vers le début de liste d'env
// 	char		**envp;			// Tableau envp (à partir de env_list pr execve)
// 	int			last_status;	// Stocker $? (le code de retour)
// 	t_ast_node	*ast_root;		// Ptr vers la racine de l'AST courant (free)
// }	t_minishell;

t_minishell	*init_ms(t_minishell *ms)
{
	ms = malloc(sizeof(t_minishell));
	if (ms)
	{
		ms->env_list = init_env(ms);
		ms->envp = NULL;
		ms->last_status = 0;
		ms->ast_root = NULL;
	}
	return (ms);
}
