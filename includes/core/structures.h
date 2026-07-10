/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:37:30 by lgervet           #+#    #+#             */
/*   Updated: 2026/07/07 02:33:45 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_state
{
	GENERAL,
	IN_QUOTE,
}	t_state;

typedef struct s_lexer_state
{
	t_state	state;
	int		i;
}	t_lexer_state;

typedef enum e_token_type
{
	TOK_WORD,
	TOK_PIPE,
	TOK_AND,
	TOK_OR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_APPEND,
	TOK_HEREDOC,
	TOK_PAREN_LEFT,
	TOK_PAREN_RIGHT,
	TOK_HEREDOC_QUOTED,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL,
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				**args;
	t_redir				*redirs;
	struct s_ast_node	*subshell_child;
}	t_ast_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	t_env		*env_list;
	char		**envp;
	int			last_status;
	t_ast_node	*ast_root;
	bool		debug;
}	t_minishell;

#endif
