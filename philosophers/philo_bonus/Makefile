NAME = philo_bonus
FSAN = philo_bonus_fsan
CFLAGS = -c -Wall -Wextra -Werror -Iincludes

SRCS = $(addprefix srcs/, \
	   check_av_bonus.c \
	   utils_philo_bonus.c \
	   utils_bonus.c \
	   main_philo_bonus.c \
	   program_initialisation_bonus.c \
	   execute_program_bonus.c \
	   )

OBJS = $(SRCS:.c=.o)

INC = includes/philo_bonus.h

INCLUDE = -pthread -g

define ascii
		@echo "$(shell tput setaf 5)"
		@echo " ==============================================================="
		@echo " *        _     _ _                       _                    * "
		@echo " *  _ __ | |__ (_) | ___  ___  ___  _ __ | |__   ___ _ __ ___  * "
		@echo " * | '_ \| '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __| * "
		@echo " * | |_) | | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \ * "
		@echo " * | .__/|_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/ * "
		@echo " * |_|                             |_|       A 42Paris project * "
		@echo " *                                                   by jsemel * "
		@echo " =============================================================== "
endef

bonus: all

all: $(NAME)

f: $(FSAN)

ascii:
	@clear
	$(call ascii)

%.o:%.c
	@cc $(CFLAGS) -c $< -o $@

$(NAME):$(OBJS) $(INC)
	@make -s ascii
	@make -s norminette
	@echo -n "$(shell tput setaf 5) Compiling binary : $(shell tput sgr0)"
	@cc $(INCLUDE) -o $(NAME) $(OBJS)
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

$(FSAN):$(OBJS) $(INC)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) Compiling binary with -fsanitize=thread: $(shell tput sgr0)"
	@cc $(INCLUDE) -o $(FSAN) $(OBJS) -fsanitize=thread
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

norminette:
	@if norminette @$(SRCS) $(INC) > /dev/null; then\
        echo "$(shell tput setaf 5) Norminette : [OK]$(shell tput sgr0)";\
    else\
        echo "$(shell tput setaf 5) Norminette : $(shell tput setaf 1)[KO]$(shell tput sgr0)";\
    fi
	@sleep 0.2

clean:
	@make -s ascii
	@sleep 0.2
	@echo -n "$(shell tput setaf 5) Deleting objects : $(shell tput sgr0)"
	@rm -rf $(OBJS)
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

fclean: clean
	@echo -n "$(shell tput setaf 5) Deleting binary : $(shell tput sgr0)"
	@rm -rf $(NAME) $(FSAN)
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

re: fclean all
