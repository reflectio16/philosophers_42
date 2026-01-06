# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meelma <meelma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/27 15:45:16 by meelma            #+#    #+#              #
#    Updated: 2025/12/09 17:02:53 by meelma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	cc 
CFLAGS	=	-Wall -Wextra -Werror -g -pthread

SRC		=	main.c init_data.c utils.c parsing.c simulation.c \
			actions.c time_utils.c monitor.c cleanup.c \
			mutex.c mutex_set_get.c threads.c write.c
OBJS	=	$(SRC:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "✅ Successfully built $(NAME)"

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean	:	
			rm -f $(OBJS)
			@echo "Objects cleaned"

fclean	:	clean
			rm -f $(NAME)
			@echo "Full clean done"

re		:	fclean all

.PHONY: all clean fclean re
