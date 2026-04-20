/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:52:23 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/20 10:44:21 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

void	expand_token_list(t_minishell *ms, t_token *head);
char	*check_for_var(char *str);
int		get_key_len(char *dollar_ptr);

#endif