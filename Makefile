NAME = minishell

#########
RM = rm -f
CC = cc
CFLAGS = -Werror -Wextra -Wall #-g -fsanitize=address
#########

#########
FILES = main parser lst_functions add_token errors_parser

FILES += expander exp_str exp_redir exp_dollar exp_dollar_utils exp_dbl_q 

FILES += executor init_cmd redirections errors_exec heredoc exec_cmd free_functions

FILES += ft_env ft_export ft_unset ft_pwd ft_cd ft_exit ft_echo signals aux_builtins env mini_loop


SRC = $(addsuffix .c, $(FILES))


vpath %.c srcs srcs/parser srcs/executor srcs/builtins srcs/expander srcs/signals

#########

#########
OBJ_DIR = objs
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
#########

########
READLINE = inc/readline
READLINE_FLAGS = -L$(READLINE) -lreadline -ltermcap -lft
LIBFT = inc/libft
LIBFT_FLAGS = -L$(LIBFT) -lft
########


#########
$(OBJ_DIR)/%.o: %.c	
	@mkdir -p $(@D)
	${CC} -MMD $(CFLAGS) -c -I inc -I inc/readline -I inc/libft -DREADLINE_LIBRARY $< -o $@

all: conf
	@$(MAKE) -C $(READLINE) --no-print-directory
	@$(MAKE) -C $(LIBFT) --no-print-directory
	$(MAKE) $(NAME) --no-print-directory

conf:
	@if [ ! -f $(READLINE)config.status ]; then\
		cd $(READLINE) && ./configure &> /dev/null; \
		echo "✅ ==== $(G)$(ligth)Create config.status$(E)==== ✅"; \
	fi

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(READLINE_FLAGS) -DREADLINE_LIBRARY $(LIBFT_FLAGS)
	@echo "\033[3;36mEVERYTHING DONE  "

clean:
	$(MAKE) clean -C $(READLINE) --no-print-directory
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
