/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:37:07 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/04 10:54:25 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* ==== INITIALIZATION ==== */
t_minishell	*init_ms(t_minishell *ms);
t_env		*init_env(void);

/* ==== UTILITIES ==== */
void	print_env_list(t_env *root);

#endif
