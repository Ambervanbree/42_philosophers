# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 09:37:23 by avan-bre          #+#    #+#              #
#    Updated: 2022/01/10 16:36:59 by avan-bre         ###   ########.fr        #
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
CFLAGS	:=	-Wall -Werror -Wextra $(IFLAGS) -fsanitize=thread
SRCS	=	philo.c philo_utils.c threads.c actions.c mutexes.c
OBJS	=	$(SRCS:.c=.o)

################################################################################
#                                 RULES                                        #
################################################################################

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	@echo "Compiling sources.."
	$(CC) $(IFLAGS) $(TFLAGS) $(OBJS) -o $@ -fsanitize=thread
	@echo "Ready!"

clean:
	$(RM) $(OBJS) ${B_OBJS}
	@echo "Removed objects"

fclean:		clean
	$(RM) $(NAME) ${B_NAME}
	@echo "Removed executable files"

re:			clean all

.PHONY:		re, all, clean, fclean
