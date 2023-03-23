# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 15:23:01 by asouchet          #+#    #+#              #
#    Updated: 2023/03/23 13:03:28 by asouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ECHO = @echo
PRINT = @printf
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
INVERT = \033[7m
RESETTXT = \033[0m
BOLD = \033[1m

SRC_PATH = src/
SRC = main.c pipex_utils.c modified_function.c fork_utils.c
SRCS = $(addprefix $(SRC_PATH),$(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:%.c=%.o)
OBJS = $(addprefix $(OBJ_PATH),$(OBJ))

NAME 	= pipex
AR 		= ar rcs
CC		= gcc
RM		= rm -f

INCLUDES = -I includes/ -I ./libft/

OPTIONS = -L ./libft -lft
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		$(ECHO) "$(YELLOW)Compilation de pipex...$(RESETTXT)"
		@ cd ./libft && $(MAKE)
		@ gcc $(CFLAGS) $(INCLUDES) $(OPTIONS) $(OBJS) -o $@ 
		$(ECHO) "$(GREEN)$(BOLD)Compilation Terminée !!!$(RESETTXT)"

bonus: $(NAME)
		cd ./libft && cp libft.a ./pipex/pipex.a
		$(AR) pipex.a $(OBJS)

%.o:$(SRC_PATH)%.c
		$(PRINT) "$(YELLOW)Generation des objets...$(RESETTXT)\r"
		@mkdir -p $(OBJ_PATH)
		@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $(OBJ_PATH)$@

clean:
		$(ECHO) "$(RED)Suppression des objets...$(RESETTXT)"
		@$(RM) $(OBJS)
		@cd ./libft && $(MAKE) clean
		$(ECHO) "$(GREEN)$(BOLD)Terminé !$(RESETTXT)"

fclean:	clean
		$(ECHO) "$(RED)Suppression de pipex et libft.a...$(RESETTXT)"
		@$(RM) $(NAME)
		@cd ./libft && $(MAKE) fclean
		$(ECHO) "$(GREEN)$(BOLD)Terminé !$(RESETTXT)"
		
re:		fclean all

.PHONY: all clean fclean re 