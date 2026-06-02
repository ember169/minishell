/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskn <mskn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 12:52:47 by mskn              #+#    #+#             */
/*   Updated: 2026/06/02 12:55:35 by mskn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

void	print_ast(t_ast_node *node, int level);
void	print_tok_list(t_token *token);
void	print_env_list(t_env *root);
void	print_cmd_node(t_ast_node *node);
int		wrong_usage_message(int has_error);

#endif