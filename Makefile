# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykopiika <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/26 16:10:54 by ykopiika          #+#    #+#              #
#    Updated: 2019/04/26 16:29:22 by ykopiika         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= wolf3d

SRC    :=	main.c\
			w_error.c\
			w_event.c\
			w_key_hook.c\
			w_print_wall.c\
			w_raycasting.c\
			w_valid_map.c

#---------- set dir ------------
SRC_PATH := $(CURDIR)/src
OBJ_PATH := $(CURDIR)/obj
OBJ_SRC := $(SRC:.c=.o)
OBJ_SRC := $(addprefix $(OBJ_PATH)/, $(OBJ_SRC))
SRC := $(addprefix $(SRC_PATH)/, $(SRC))

#---------- CC stuff -----------
CC := gcc
FLAG_CC = -Wall -Wextra -Werror

#---------- SDL stuff ----------
SDL_INC =  -I $(CURDIR)/frameworks/SDL2.framework/Headers/ 		\
           -I $(CURDIR)/frameworks/SDL2_image.framework/Headers

FLAG_FRM =	-F frameworks

SDL_FLAGS =	-rpath frameworks		\
			-framework SDL2 		\
			-framework SDL2_image

#---------- libft -----------
LIB_INC =	-I libft/ \
			-I inc/
LIB_FT = libft/libft.a

all: $(NAME)

$(LIB_FT):
	@make -C libft/

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(LIB_FT) $(OBJ_SRC)
	$(CC) $(OBJ_SRC) $(FLAG_FRM) $(SDL_FLAGS) -L libft -lft -o $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(FLAG_CC) $(FLAG_FRM) $(SDL_INC) $(LIB_INC) -c $< -o $@

clean:
	@make -C libft/ clean
	/bin/rm -rf $(OBJ_SRC)
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make -C libft/ fclean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re
