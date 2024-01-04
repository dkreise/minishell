NAME = minishell

#########
RM = rm -f
CC = cc
CFLAGS = -Werror -Wextra -Wall #-g -fsanitize=address
#########

#########
FILES_DIANA += parser lst_functions
FILES = main
# FILES += executor

SRC = $(addsuffix .c, $(FILES))

vpath %.c srcs srcs/parser
#########

#########
OBJ_DIR = objs
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
#########

########
READLINE = inc/readline
READLINE_FLAGS = -lreadline -ltermcap #-lhistory -lft
LIBFT = inc/libft
LIBFT_FLAGS = -L$(LIBFT) -lft
########


#########
$(OBJ_DIR)/%.o: %.c	
	@mkdir -p $(@D)
	${CC} $(CFLAGS) -Iinc/libft -MMD -c $< -o $@

all:
#	@$(MAKE) -C $(READLINE) --no-print-directory
	@$(MAKE) -C $(LIBFT) --no-print-directory
	$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(READLINE_FLAGS) $(LIBFT_FLAGS) -g -fsanitize=address -o $(NAME)
	@echo "EVERYTHING DONE  "

clean:
	#$(MAKE) clean -C $(READLINE) --no-print-directory
	$(MAKE) clean -C $(LIBFT) --no-print-directory
	$(RM) $(OBJ) $(DEP) --no-print-directory
	$(RM) -r $(OBJ_DIR) --no-print-directory
	@echo "OBJECTS REMOVED   "

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(RM) $(NAME) --no-print-directory
	@echo "EVERYTHING REMOVED   "

re:	fclean all

.PHONY: all clean fclean re

-include $(DEP)

#########
