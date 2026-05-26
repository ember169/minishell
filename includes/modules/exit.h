/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 17:56:29 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/20 17:58:34 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

int		wrong_usage_message(int has_error);
void	print_tok_list(t_token *token);
void	print_env_list(t_env *root);
void	clean_ms(t_minishell *ms);

#endif