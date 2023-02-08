# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: deman_wolf <deman_wolf@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 13:58:24 by faksouss          #+#    #+#              #
#    Updated: 2023/02/08 03:09:49 by deman_wolf       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = errors.c\
		actions.c\
		ll_utils.c\
		start_dinning.c\
		main.c\

OBJ_D = obj

OBJ = $(addprefix $(OBJ_D)/,$(SRC:.c=.o))

FLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -rf

INC = philo.h

NAME = philo

all : $(OBJ_D) $(NAME)

$(NAME) : $(OBJ)
	cc $(FLAGS) $^ -o $@

$(OBJ_D) :
	mkdir $@

$(OBJ_D)/%.o : %.c $(INC)
	@cc $(FLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ_D)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all re clean fclean $(NAME)

.SILENT : all re clean fclean $(NAME) $(OBJ_D)
