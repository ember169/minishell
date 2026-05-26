/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:51:53 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/18 10:51:56 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void		clean_ms(t_minishell *ms);
void		add_to_history(char *str);
void		print_env_list(t_env *root);

#endif
