NAME = minishell

#########
RM = rm -f
CC = cc
CFLAGS = -Werror -Wextra -Wall -g -fsanitize=address
#########

#########
#FILES += parser lst_functions add_token errors_parser executor init_cmd redirections errors_exec

FILES = main ft_env ft_export ft_unset ft_pwd ft_cd ft_exit ft_echo signals

SRC = $(addsuffix .c, $(FILES))


vpath %.c srcs srcs/parser srcs/executor srcs/builtins srcs/signals
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
	${CC} -MMD $(CFLAGS) -c -I inc/readline -I inc/libft $< -o $@

all: conf
	@$(MAKE) -C $(READLINE) --no-print-directory
	@$(MAKE) -C $(LIBFT) --no-print-directory
	$(MAKE) $(NAME) --no-print-directory

conf:
	@if [ ! -f $(READL)config.status ]; then\
		cd $(READL) && ./configure &> /dev/null; \
		echo "✅ ==== $(G)$(ligth)Create config.status$(E)==== ✅"; \
	fi

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(READLINE_FLAGS) $(LIBFT_FLAGS)
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

# ########
# NAME = minishell
# CC = gcc
# RM = rm -rf
# FLAGS = -Wall -Wextra -Werror  -g #-fsanitize=address
# ################################################################################
# #  Bar                                                                         #
# ################################################################################
# CURRENT_FILE = 0
# PROGRESS_BAR :=
# ################################################################################
# #                               SOURCES                                        #
# ################################################################################
# SRC = main.c
# LIBFT = ./inc/libft/
# READL = ./inc/readline/
# L_SRC = ./src
# L_LIB = ./inc/libft/libft.a
# L_RDL = ./inc/readline/libreadline.a
# L_HIT = ./inc/readline/libhistory.a 
# INC		=	-I ./inc/\
# 			-I ./lib/libft/\
# 			-I ./lib/readline/
# ################################################################################
# #                               DIRECTORIES                                    #
# ################################################################################
# D_OBJ = $(L_SRC)/obj
# OBJ = $(addprefix $(D_OBJ)/, $(SRC:.c=.o))
# DEP = $(addprefix $(D_OBJ)/, $(SRC:.c=.d))
# ################################################################################
# #                               BOLD COLORS                                    #
# ################################################################################
# E = \033[m
# R = \033[31m
# G = \033[32m
# Y = \033[33m
# B = \033[34m
# P = \033[35m
# C = \033[36m
# ################################################################################
# #  FONT                                                                        #
# ################################################################################
# ligth = \033[1m
# dark = \033[2m
# italic = \033[3m
# ################################################################################
# #                               MAKE RULES                                     #
# ################################################################################
# #Rules
# all: conf dir $(NAME)
# -include $(DEP)
# conf:
# 	@if [ ! -f $(READL)config.status ]; then\
# 		cd $(READL) && ./configure &> /dev/null; \
# 		echo "✅ ==== $(G)$(ligth)Create config.status$(E)==== ✅"; \
# 	fi
# dir:
# 	make -C $(LIBFT) --no-print-directory
# 	make -C $(READL) --no-print-directory &> /dev/null
# 	-mkdir  $(D_OBJ)
# 	-mkdir	$(D_OBJ)/built-ins
# 	-mkdir	$(D_OBJ)/execute
# 	-mkdir	$(D_OBJ)/get
# 	-mkdir  $(D_OBJ)/parse
# $(D_OBJ)/%.o:$(L_SRC)/%.c Makefile
# 	$(CC) -MMD $(FLAGS) -c -D READLINE_LIBRARY=1 $< -o $@ $(INC)
# 	$(eval CURRENT_FILE := $(shell echo $$(($(CURRENT_FILE) + 1)))) \
# 	$(eval PROGRESS_BAR := $(shell awk "BEGIN { printf \"%.0f\", $(CURRENT_FILE)*100/$(TOTAL_FILES) }")) \
# 	printf "\r$B$(ligth)⏳Compiling libft:$E $(ligth)%-30s [$(CURRENT_FILE)/$(TOTAL_FILES)] [%-50s] %3d%%\033[K" \
# 	"$<..." "$(shell printf '$(G)█%.0s$(E)$(ligth)' {1..$(shell echo "$(PROGRESS_BAR)/2" | bc)})" $(PROGRESS_BAR)
	
# 	@if [ $(PROGRESS_BAR) = 100 ]; then \
# 		echo "$(B) All done$(E)"; \
# 	fi
# $(NAME): $(OBJ)
# 	$(CC) $(FLAGS) $(OBJ) $(L_LIB) $(L_RDL) $(L_HIT) -ltermcap -lreadline -o $(NAME) $(INC)
# 	echo "\n\n✅ ==== $(B)$(ligth)Project minishell compiled!$(E) ==== ✅"
# ################################################################################
# #                               CLEAN                                          #
# ################################################################################

# .PHONY: all clean fclean re
# fclean: clean
# 	$(RM) $(NAME)
# 	make fclean -C $(LIBFT) --no-print-directory
# 	make clean -C $(READL) --no-print-directory &> /dev/null
# 	echo "✅ ==== $(P)$(ligth)minishell executable files and name cleaned!$(E) ==== ✅\n"
	
# clean:
# 	$(RM) $(D_OBJ)
# 	make clean -C $(LIBFT) --no-print-directory
# 	make -C $(READL) --no-print-directory &> /dev/null
# 	echo "✅ ==== $(P)$(ligth)minishell object files cleaned!$(E) ==== ✅"
# re: fclean all
# TOTAL_FILES := $(words $(SRC))
# .SILENT: