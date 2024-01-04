# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/08 16:57:18 by dkreise           #+#    #+#              #
#    Updated: 2023/10/21 15:53:11 by dkreise          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
		ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRCSBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
 			
OBJS = ${SRCS:.c=.o}
OBJSBONUS = ${SRCSBONUS:.c=.o}

NAME = libft.a
HEADER = libft.h

CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

#implicit method
%.o:%.c 	$(HEADER) Makefile 
			$(CC) $(CFLAGS) -c $< -o $@

#your mothods
all: 		${NAME}

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

bonus:		${OBJS} ${OBJSBONUS}
			ar rcs ${NAME} ${OBJS} ${OBJSBONUS}
			# this create a tinny empty bonus file, to check relink
			@touch $@ 

clean:
			${RM} ${OBJS} ${OBJSBONUS}

fclean: 	clean	
			${RM} ${NAME}
			${RM} bonus

re:			fclean all

.PHONY: all clean fclean re 
