/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:52:23 by lgervet           #+#    #+#             */
/*   Updated: 2026/05/26 09:38:14 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

void		expand_token_list(t_minishell *ms, t_token *head);
char		*check_for_var(char *str);
int			get_key_len(char *dollar_ptr);
void		get_env_var(t_minishell *ms, char *dollar, char **var);
char		is_quote(char c);
bool		is_quoted_star(char *raw);
char		*expand_loop(t_minishell *ms, char *str, char *ret);
t_token		*expand_path(t_token *current);
bool		match_glob(char *pattern, char *str);
void		sort_matches(char **arr, int n);
int			count_dir_entries(char *path);
int			count_matches(char **filenames, char *pattern);
void		free_str_array(char **arr);

#endif