/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:37:07 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/04 14:33:24 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/* ==== INITIALIZATION ==== */
t_minishell	*init_ms(t_minishell *ms);
t_env		*init_env(t_minishell *ms);
/* ==== UTILITIES ==== */
void		print_env_list(t_env *root);
void		clean_ms(t_minishell *ms);

#endif
