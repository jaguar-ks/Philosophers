# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faksouss <faksouss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 13:58:24 by faksouss          #+#    #+#              #
#    Updated: 2023/02/12 00:47:53 by faksouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = actions.c\
		ll_utils.c\
		start_dinning.c\
		main.c\

OBJ_D = obj

OBJ = $(addprefix $(OBJ_D)/,$(SRC:.c=.o))

FLAGS = -Wall -Wextra -Werror 

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
