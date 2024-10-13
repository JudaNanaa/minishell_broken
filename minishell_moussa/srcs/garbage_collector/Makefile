#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#


SRCS =	srcs/garbage_collector.c	\
		srcs/garbage_utils_1.c		\
		srcs/garbage_utils_2.c		\
		srcs/garbage_collector_2.c	\

#	Loading bar	#

G                = \e[92m
X                 = \e[0m
BAR_SIZE        = 50

TOTAL_FILES        := $(words $(SRCS))
COMPILED_FILES    := 0

#				#

NAME = ./garbage_collector.a

OBJS = $(SRCS:.c=.o)

CC = cc

CC_FLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

%.o : %.c
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@$(eval COMPILED_FILES := $(shell echo $$(($(COMPILED_FILES)+1))))
	@echo -n " "
	@for i in `seq 1 $(shell echo "$$(($(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "$(G)▰$(X)" ; \
	done
	@for i in `seq 1 $(shell echo "$$(($(BAR_SIZE)-$(COMPILED_FILES)*$(BAR_SIZE)/$(TOTAL_FILES)))")`; do \
		echo -n "▱" ; \
	done
	@echo -n " [$(shell echo "scale=2; $(COMPILED_FILES)/$(TOTAL_FILES) * 100" | bc)%] "
	# @echo -n "["
	# @printf "%d/%d" $(COMPILED_FILES) $(TOTAL_FILES)
	# @echo -n "] "
	# @printf "%s" $(notdir $<)
	@printf "\e[0K\r"

$(NAME): $(OBJS) $(SRCS)
	@ar cr $(NAME) $(OBJS)
# @echo ""
# @echo "$(BLUE)Garbage Collector done ✅$(END)"
# @echo ""

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: clean fclean all