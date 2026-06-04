# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: v <v@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/19 13:42:29 by lgervet           #+#    #+#              #
#    Updated: 2026/06/04 18:24:17 by v                ###   ########.fr        #
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
SRC_FILES   := main.c \
               history.c \
               debug/debug_ast_print_utils.c \
               debug/debug_errors.c \
               debug/debug_print.c \
               env/env.c \
               env/env_checkers.c \
               env/env_utils.c \
               executor/exec_ast.c \
               executor/exec_dispatcher.c \
               exit/exit.c \
               expander/expander.c \
               expander/expander_path_expand.c \
               expander/expander_path_utils.c \
               expander/expander_quote_expand.c \
               expander/expander_quote_utils.c \
               expander/expander_var_utils.c \
               lexer/handling.c \
               lexer/lexer.c \
               lexer/lexer_utils.c \
               parser/ast_utils.c \
               parser/build_ast.c \
               parser/free_ast.c \
               parser/handle_redir.c \
               parser/parse_subshell.c \
               parser/heredoc.c \
               executor/exec_ast.c \
               executor/leo_test.c \
               executor/redirections.c
			   
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

re: fclean all

.PHONY: all clean fclean re