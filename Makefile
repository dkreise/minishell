NAME = minishell

#########
RM = rm -f
CC = cc
CFLAGS = -Werror -Wextra -Wall -g -fsanitize=address
#########

#########
FILES = main parser lst_functions add_token errors_parser

FILES += expander exp_redir exp_dollar

FILES += executor init_cmd redirections errors_exec heredoc

FILES += ft_env ft_export ft_unset ft_pwd ft_cd ft_exit ft_echo

SRC = $(addsuffix .c, $(FILES))


vpath %.c srcs srcs/parser srcs/executor srcs/builtins srcs/expander
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
	$(CC) $(CFLAGS) $(OBJ) $(READLINE_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "\033[3;36mEVERYTHING DONE  "

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
