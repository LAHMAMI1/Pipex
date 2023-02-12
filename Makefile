# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 22:35:21 by olahmami          #+#    #+#              #
#    Updated: 2023/02/11 22:54:41 by olahmami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
NAME		=	pipex
CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	pipex.c

LIBS		=	libft.a

INCLUDES	=	$(LIBS:%=Libft/libft.a)

OBJ = ${SRCS:.c=.o}

all: $(LIBS) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)

libs: $(LIBS)

$(LIBS):
	@make -C Libft

clean:
	@rm -f ${OBJ}
	@make -C Libft clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(INCLUDES)
	@make -C Libft fclean

re: fclean all

.PHONY: all