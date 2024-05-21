# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gasroman <gasroman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 23:42:36 by gasroman          #+#    #+#              #
#    Updated: 2024/05/21 12:10:43 by gasroman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =============================== VARIABLES ================================== #
NAME = pipex
CC = gcc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror -g

# =========================== SOURCES ======================================== #
SRC_PATH = src/
SRC = pipex.c
LIB_PATH = ./libft/
LIB = $(LIB_PATH)libft.a
INC =	-I ./inc/

# =========================== DIRECTORIES ==================================== #
DIR_OBJ = $(SRC_PATH)obj/
OBJ = $(addprefix $(DIR_OBJ), $(SRC:.c=.o))
DEP = $(addprefix $(DIR_OBJ), $(SRC:.c=.d))


# =========================== BOLD COLORS ==================================== #

E = \033[m
R = \033[31m
G = \033[32m
Y = \033[33m
B = \033[34m
P = \033[35m
C = \033[36m
#Font
ligth = \033[1m
dark = \033[2m
italic = \033[3m


# ========================== MAKE RULES ===================================== #
all: dir $(NAME)

-include $(DEP)

dir:
	@make -C $(LIB_PATH)
	@mkdir -p $(DIR_OBJ)

print:
	echo "$(DIR_OBJ)"
	echo "$(OBJ)"
$(DIR_OBJ)%.o: $(SRC_PATH)%.c
	@$(CC) -MMD $(FLAGS) -c $< -o $@ $(INC)
	@printf "\r$(G)$<$(E) to $(P)$@$(E)                           "

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME) $(INC)

# ========================== CLEAN   ===================================== #

fclean: clean
	$(RM) $(NAME) $(NAME)

clean:
	$(RM) $(DIR_OBJ)
	@make clean -C $(LIB_PATH)

re: fclean all
.PHONY: clean fclean re
.SILENT: