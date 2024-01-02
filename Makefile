NAME = minishell

#########
RM = rm -f
CC = cc
CFLAGS = -Werror -Wextra -Wall #-g -fsanitize=address
#########

#########
FILES = main

SRC = $(addsuffix .c, $(FILES))

vpath %.c srcs srcs/executor
#########

#########
OBJ_DIR = objs
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
#########

########
READLINE = inc/readline
READLINE_FLAGS = -lreadline -ltermcap #-lhistory -lft
########


#########
$(OBJ_DIR)/%.o: %.c	
	@mkdir -p $(@D)
	@${CC} $(CFLAGS) -MMD -c $< -o $@

all:
	#@$(MAKE) -C $(READLINE) --no-print-directory
	$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(READLINE_FLAGS) -o $(NAME)
	@echo "EVERYTHING DONE  "

clean:
	#$(MAKE) clean -C $(READLINE) --no-print-directory
	$(RM) $(OBJ) $(DEP) --no-print-directory
	$(RM) -r $(OBJ_DIR) --no-print-directory
	@echo "OBJECTS REMOVED   "

fclean: clean
	$(RM) $(NAME) --no-print-directory
	@echo "EVERYTHING REMOVED   "

re:	fclean all

.PHONY: all clean fclean re

-include $(DEP)

#########
