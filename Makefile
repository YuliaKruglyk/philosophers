# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykruhlyk <ykruhlyk@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:58:58 by ykruhlyk          #+#    #+#              #
#    Updated: 2023/01/16 17:24:07 by ykruhlyk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	philo

SRCS	=	main.c include.c init.c time.c routine.c time_to_die.c 

OBJ		=	$(SRCS:%.c=%.o)
HEADER	=	philo.h
CC 		=	gcc
FLAGS	=	-g -Wall -Wextra -Werror -fsanitize=thread -g
RM		=	rm -rf

Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"

all:		$(NAME)

$(NAME):	$(OBJ)
				$(CC) $(FLAGS) $(OBJ) -o $(NAME)
				@echo $(G)$(NAME) compiled
	
%.o:		%.c $(HEADER)
				$(CC) $(FLAGS) -c $< -o $@ 
				
clean:
			@$(RM) $(OBJ)
			@echo Cleaning $(NAME) succeed

fclean:		clean
			@$(RM) $(NAME)
			@echo Deleting $(NAME) succeed

re:			fclean all
			@echo $(Y)Remake done

.PHONY:		all	clean	fclean	re
