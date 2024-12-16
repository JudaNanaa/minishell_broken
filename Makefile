# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 12:57:50 by madamou           #+#    #+#              #
#    Updated: 2024/10/10 05:07:1 by ibaby            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
PURPLE=	$(shell tput -Txterm setaf 5)
END= 	$(shell tput -Txterm sgr0)

CC = cc

C_FLAGS = -Wall -Wextra -Werror -g3

SRCS_DIR = srcs/

PARSING = $(addprefix parsing/, before_parsing.c lexer.c parser_utils.c parser.c here_doc.c expand.c)

ERROR = $(addprefix error_utils/, err_utils.c error_code.c free_and_exit.c print_err.c)

SIGNALS = $(addprefix signal/, signal.c signal_utils.c)

AST = $(addprefix ast/, ast_moussa.c)

# AST = $(addprefix ast/, ast.c)

EXEC = $(addprefix exec/, exec.c exec_utils.c)

MINISHELL = $(addprefix minishell_loop/, minishell.c)

BUILTINS = $(addprefix builtins/, env.c cd.c echo.c export.c pwd.c exit.c unset.c alias.c)

ENV = $(addprefix environement/, environement_variables.c environement_variables_utils.c)

FEATURES = $(addprefix features/, history.c prompt_utils.c prompt.c readline_history.c)

UTILS = $(addprefix utils/, utils.c)

WILDCARDS = $(addprefix wildcard/, wildcard_moussa.c wildcard_utils_moussa.c)

OBJS_DIR = .objets/

SRCS = main.c tests_utils.c $(PARSING) $(MINISHELL) $(SIGNALS) $(AST) $(ERROR) $(ENV) $(UTILS) $(BUILTINS) $(EXEC) $(FEATURES) $(WILDCARDS)

SRCS := $(SRCS:%=$(SRCS_DIR)/%)

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

DIR_DUP = mkdir -p $(@D)

G				= $(BLUE)
X 				= $(END)
BAR_SIZE		= 50

TOTAL_FILES		:= $(words $(SRCS))
COMPILED_FILES	:= 0

GARBAGE_DIR = srcs/garbage_collector/
GARBAGE = $(GARBAGE_DIR)garbage_collector.a

LIBFT = libft.a

NAME = ./minishell

all : $(LIBFT) $(GARBAGE) $(NAME)

$(LIBFT) :
	@echo
	@echo "👷$(GREEN)compiling libft$(END)👷"
	@make -sC ./libft
	@echo
	@echo "👷$(GREEN)libft compilation done$(END)👷"

$(GARBAGE) :
	@echo
	@echo "👷$(GREEN)compiling garbage collector$(END)👷"
	@make -sC $(GARBAGE_DIR)
	@echo
	@echo "👷$(GREEN)garbage collector compilation done$(END)👷"

$(NAME) : message $(OBJS)
	@$(CC) $(C_FLAGS) $(OBJS) srcs/garbage_collector/garbage_collector.a -L ./libft -lft -lreadline -o $@
	@echo
	@echo "💻$(BLUE)executable created >_$(END)✅"
	@cp .supp.supp ~
	@echo

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@$(DIR_DUP)
	@$(CC) $(C_FLAGS) -c $< -o $@
	@$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES)+1))))
	@echo -n ""
	@for i in `seq 1 $(shell echo "$$(($(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "$(G)▰$(X)" ; \
	done
	@for i in `seq 1 $(shell echo "$$(($(BAR_SIZE)-$(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "▱" ; \
	done
	@echo -n " [$(shell echo "scale=2; $(COMPILED_FILES)/$(TOTAL_FILES) * 100" | bc)%] "
# @echo -n ""
# @printf "%d/%d" $(COMPILED_FILES) $(TOTAL_FILES)
# @echo -n " "
# @printf "%s" $(notdir $<)
	@printf "\e[0K\r"

message :
	@echo
	@echo "$(BLUE)🔩compiling minishell🔩$(END)"
	
leak : all
	@valgrind --leak-check=full --show-below-main=no --show-leak-kinds=all --track-fds=yes    --trace-children=yes --suppressions=.supp.supp ./minishell

push:
	@python3 -m c_formatter_42 $(addprefix $(SRCS_DIR), main.c $(PARSING) $(PROMPT) $(SIGNALS) \
	 $(BINARY_TREE) $(ERROR) $(EXEC) $(ENV) $(UTILS) $(BUILTINS)) | norminette | grep Error
	@git add .
	@echo -n "$(BLUE)Enter your commit message: $(END)"
	@read commit_message; \
	git commit -m "$$commit_message"; \
	git push; \
	echo "$(YELLOW)All has been pushed with '$$commit_message' in commit$(END)"

debug : all
	@lldb $(NAME)

docker:
	@if [ -z $$(docker images -q minishell-app) ]; then \
		echo "🐳$(BLUE)Image minishell-app not found, work in progress...$(END)🐳"; \
		docker-compose build; \
		echo "🐳$(BLUE)Docker container is built $(END)✅"; \
	fi
	@echo "🐳$(BLUE)Docker container is built $(END)✅"
	@docker-compose run app

clean : 
	@rm -rf $(OBJS_DIR)
	@make clean -sC ./libft
	@make clean -sC $(GARBAGE_DIR)
	@echo "🧼🧼$(PURPLE)objects cleaned$(END)🧼🧼"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -sC ./libft
	@make fclean -sC $(GARBAGE_DIR)
	@echo "🧼🧼$(PURPLE)executable cleaned$(END)🧼🧼"

re : fclean all

.PHONY : all clean fclean re debug push leak docker 
