# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: v <v@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/19 13:42:29 by lgervet           #+#    #+#              #
#    Updated: 2026/04/09 12:32:06 by v                ###   ########.fr        #
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
               init/s_env.c \
			   init/s_env_checkers.c \
               init/s_minishell.c \
			   utils/chained_list_printer.c \
			   utils/heap_cleanup.c \
			   utils/chained_list_requests.c \
			   utils/lexer_utils.c \
			   lexer/fsm.c \
			   lexer/handling.c \
			   
# Objets :
OBJS        := $(addprefix $(OBJSDIR)/, $(SRC_FILES:.c=.o))

# Règle par défaut
all: $(LIBFT) $(NAME)

# Compilation de la Libft
$(LIBFT):
	@$(MAKE) -C $(LIBPATH)

# Linkage du binaire final
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBPATH) -lft -o $(NAME)

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