/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgervet <42@leogervet.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:37:30 by lgervet           #+#    #+#             */
/*   Updated: 2026/04/03 18:42:12 by lgervet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_token_type
{
	TOK_WORD,			// Mots classiques (ex: "ls", "-l", "fichier")
	TOK_PIPE,			// |
	TOK_AND,			// &&
	TOK_OR,				// ||
	TOK_REDIR_IN,		// <
	TOK_REDIR_OUT,		// >
	TOK_REDIR_APPEND,	// >>
	TOK_HEREDOC,		// <<
	TOK_PAREN_LEFT,		// (
	TOK_PAREN_RIGHT,	// )
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value; // Contient la string
	struct s_token	*next;
}	t_token;

// Structure pour stocker la liste des redirections d'une commande
typedef struct s_redir
{
	t_token_type	type;	// Type de redirection (<, >, >>, <<)
	char			*file;	// Nom du fichier cible ou délimiteur du heredoc
	struct s_redir	*next;
}	t_redir;

typedef enum e_node_type
{
	NODE_CMD,		// Nœud terminal : une vraie commande à exécuter
	NODE_PIPE,		// Nœud opérateur : |
	NODE_AND,		// Nœud opérateur : &&
	NODE_OR,		// Nœud opérateur : ||
	NODE_SUBSHELL,	// Nœud parenthèse : exécution isolée
}	t_node_type;

// La structure de l'AST
typedef struct s_ast_node
{
	t_node_type			type;

	// Pour les nœuds opérateurs (PIPE, AND, OR)
	struct s_ast_node	*left;
	struct s_ast_node	*right;

	// Pour les nœuds commandes (NODE_CMD)
	char				**args;		// Tableau d'arguments execve
	t_redir				*redirs;	// Liste des redirections de la commande

	// Pour les sous-shells (parenthèses)
	struct s_ast_node	*subshell_child; // AST dans les ()
}	t_ast_node;

typedef struct s_env
{
	char			*key;	// Ex: "PATH"
	char			*value;	// Ex: "/usr/bin:/bin"
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	t_env		*env_list;		// Pointeur vers le début de liste d'env
	char		**envp;			// Tableau envp (à partir de env_list pr execve)
	int			last_status;	// Stocker $? (le code de retour)
	t_ast_node	*ast_root;		// Ptr vers la racine de l'AST courant (free)
}	t_minishell;

#endif
