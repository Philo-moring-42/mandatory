# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hogkim <hogkim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/22 13:33:12 by hjeong            #+#    #+#              #
#    Updated: 2022/08/22 20:46:38 by hogkim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wall -Wextra -pthread -g3 -fsanitize=thread 
NAME = philo

SRCS = main.c \
		ft_atoi.c \
		get_time.c \
		init_func.c \
		monitoring.c \
		parsing.c \
		philo_act.c \
		philo_act2.c \
		print.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : 
	make fclean 
	make all	

.PHONY : all clean fclean re
