NAME =  harlFilter
FLAGS = -std=c++98 -MMD -Wall -Wextra -Werror -g3
CC = c++

SRCS = main.cpp \
		utils.cpp \
		Harl.cpp \

SRCS_DIR = srcs

OBJS_DIR = obj

INC = -Iinclude

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

DEPS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.d))

define ascii
		@echo "$(shell tput setaf 5)"
		@echo "================================================================"
		printf "*    ___   ___  ___                    _       _       ___  _  *\n"
		printf "*   / __\ / _ \/ _ \   /\/\   ___   __| |_   _| | ___ / _ \/ | *\n"
		printf "*  / /   / /_)/ /_)/  /    \ / _ \ / _\` | | | | |/ _ \ | | | | *\n"
		printf "* / /___/ ___/ ___/  / /\/\ \ (_) | (_| | |_| | |  __/ |_| | | *\n"
		printf "* \____/\/   \/      \/    \/\___/ \__,_|\__,_|_|\___|\___/|_| *\n"
		printf "*                                                   Exercise06 *\n"
		@echo "================================================================"
endef

all: $(NAME)

ascii:
	@clear
	$(call ascii)

$(NAME): $(OBJS_DIR) $(OBJS)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME) $(OBJS) 
	@echo "[OK]$(shell tput sgr0)"

-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects' destination directory /$(OBJS_DIR) : "
	@mkdir -p $(OBJS_DIR)
	@echo "[OK]$(shell tput sgr0)"

clean:
	@make -s ascii
	@echo -n "$(shell tput setaf 5) clean:"
	@echo -n " Removing objects' directory /$(OBJS_DIR) : "
	@rm -rf $(OBJS_DIR)
	@echo "[OK]$(shell tput sgr0)"

fclean: clean
	@echo -n "$(shell tput setaf 5) fclean:"
	@echo -n " Removing executable [ $(NAME) ] : "
	@rm -rf $(NAME)
	@echo "[OK]$(shell tput sgr0)"

re: fclean all

.PHONY: all clean fclean