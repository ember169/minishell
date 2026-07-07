# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: v <v@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/19 13:42:29 by lgervet           #+#    #+#              #
#    Updated: 2026/07/07 02:49:59 by v                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g3

# Dossiers
SRCSDIR     := srcs
OBJSDIR     := objs
INCSDIR     := includes
LIBPATH     := libs/libft
LIBNAME     := libft.a
LIBFT       := $(LIBPATH)/$(LIBNAME)

INC         := -I $(INCSDIR) -I $(LIBPATH)/includes

# Sources :
SRC_FILES   := main/main.c \
               main/history.c \
               main/init.c \
               main/syntax.c \
               debug/debug_ast_print_utils.c \
               debug/debug_errors.c \
               debug/debug_print.c \
			   builtins/cd.c \
			   builtins/echo.c \
               builtins/env.c \
               builtins/exit.c \
               builtins/export.c \
			   builtins/pwd.c \
               builtins/unset.c \
               env/env.c \
               env/env_checkers.c \
               env/env_node_utils.c \
               env/env_utils.c \
               env/envp_array.c \
               exit/exit.c \
               expander/expander.c \
               expander/expander_path_expand.c \
               expander/expander_path_utils.c \
               expander/expander_quote_expand.c \
               expander/expander_quote_utils.c \
               expander/expander_var_utils.c \
               lexer/lexer_handling.c \
               lexer/lexer.c \
               lexer/lexer_utils.c \
               parser/ast_utils.c \
               parser/build_ast.c \
               parser/free_ast.c \
               parser/handle_redir.c \
               parser/parse_subshell.c \
               parser/heredoc.c \
               parser/parse_cmd.c \
               parser/heredoc_expand.c \
               executor/exec_ast.c \
               executor/exec_dispatcher.c \
               executor/redirections.c \
               executor/exec_path.c \
               executor/exec_builtin.c \
               executor/exec_pipe.c \
               executor/exec_utils.c \
               signals/signals.c
			   
# Objets :
OBJS        := $(addprefix $(OBJSDIR)/, $(SRC_FILES:.c=.o))

# Règle par défaut
all: $(LIBFT) $(NAME)

# Compilation de la Libft
$(LIBFT):
	@$(MAKE) -C $(LIBPATH)

# Linkage du binaire final
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBPATH) -lft -lreadline -o $(NAME)

# Compilation des objets (.c -> .o)
$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJSDIR)
	@$(MAKE) -C $(LIBPATH) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBPATH) fclean

valgrind: all
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

re: fclean all

.PHONY: all clean fclean re