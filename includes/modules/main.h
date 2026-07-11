/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 02:25:07 by v                 #+#    #+#             */
/*   Updated: 2026/07/07 02:38:21 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

bool		check_syntax(t_token *tok);
bool		ast_failed(t_minishell *ms, t_token *list);
t_minishell	*init_ms(t_minishell *ms, char **av, char **envp);

#endif