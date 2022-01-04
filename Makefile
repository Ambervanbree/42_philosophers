# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 09:37:23 by avan-bre          #+#    #+#              #
#    Updated: 2022/01/04 18:04:48 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                  INFO                                        #
################################################################################

NAME	=	philo
RM		=	@rm -rf
CC		=	@clang
IFLAGS	=	-I.
TFLAGS	=	-pthread
CFLAGS	:=	-Wall -Werror -Wextra $(IFLAGS)
SRCS	=	philo.c philo_utils.c threads.c
OBJS	=	$(SRCS:.c=.o)

################################################################################
#                                 RULES                                        #
################################################################################

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	@echo "Compiling sources.."
	$(CC) $(IFLAGS) $(TFLAGS) $(OBJS) -o $@   
	@echo "Ready!"

clean:
	$(RM) $(OBJS) ${B_OBJS}
	@echo "Removed objects"

fclean:		clean
	$(RM) $(NAME) ${B_NAME}
	@echo "Removed executable files"

re:			clean all

.PHONY:		re, all, clean, fclean
