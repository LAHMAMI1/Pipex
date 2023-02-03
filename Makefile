# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 22:35:21 by olahmami          #+#    #+#              #
#    Updated: 2023/02/03 05:38:36 by olahmami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
NAME		=	pipex
CFLAGS		=	#-Wall -Wextra -Werror

SRCS		=	pipex.c

LIBS		=	libft.a

#BONUS		=	pipex_bonus

INCLUDES	=	$(LIBS:%=Libft/libft.a)

OBJ = ${SRCS:.c=.o}

all: $(LIBS) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)

libs: $(LIBS)

$(LIBS):
	@make -C Libft

#bonus: $(BONUS)

#$(BONUS):
#	@make -C Bonus

clean:
	@rm -f ${OBJ}
	@make -C Libft clean
#	@make -C Bonus clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(INCLUDES)
	@make -C Libft fclean
#	@make -C Bonus fclean

re: fclean all

.PHONY: all