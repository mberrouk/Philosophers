# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 20:24:02 by mberrouk          #+#    #+#              #
#    Updated: 2023/07/17 02:42:36 by mberrouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c philo.c philo_intro.c philo_check.c philo_utils.c philo_clean.c

HEADERS = philo.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3

NAME = philo

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
