# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelazzou <oelazzou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 20:13:16 by oelazzou          #+#    #+#              #
#    Updated: 2020/02/19 02:08:51 by oelazzou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
LIBFT_PATH = ./libft/
INC = -I ./includes/ -I $(LIBFT_PATH)
SRC_DIR = ./src/
OBJ_DIR = ./obj/
FLAGS = -Wall -Wextra -Werror -ltermcap
SRC_NAME =  arguments.c \
			counting.c \
			error.c \
			main.c \
			node.c \
			printing.c \
			signals.c \
			utils.c \
			arrows.c \
			free_all.c \
			browsing.c \
			check_access.c \
			
SRCS = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@make -s -C $(LIBFT_PATH)
	@echo "\033[92m--> libft.a CREATED! <--"
	@gcc $(FLAGS) $(INC) $(OBJS) -L $(LIBFT_PATH) -lft -o $(NAME)
	@echo "\033[1m\033[35m--> ft_select CREATED! <--\033[0m"
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p obj
	@gcc -c $(INC) $^ -o $@
	@echo "\033[92m--> Object file Created <--"
clean:
	@echo "\033[1m\033[93m-> cleaning...\033[0m"
	@make clean -s -C $(LIBFT_PATH)
	@rm -rf $(OBJ_DIR)
	@echo "\033[92m-> libft object files REMOVED!\033[0m"
fclean: clean
	@make fclean -s -C $(LIBFT_PATH)
	@echo "\033[92m-> ft_select executable REMOVED!\033[0m"
	@rm -f $(NAME)
	@echo "\033[1m\033[31m---> Done! <----\033[0m"
re: fclean all
