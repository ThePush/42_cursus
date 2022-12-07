NAME = ircserv

FLAGS = -std=c++98 -MMD -Wall -Wextra -Werror# -g3
CC = c++

SRCS = main.cpp \
       TCPsocket.cpp \
       TCPserver.cpp \
       Channel.cpp \
       User.cpp \
       ServerOperator.cpp \
       ChannelMode.cpp \
       registerUser.cpp \
       handleClientCommands.cpp \
       utils.cpp \

SRCS_DIR = src/

OBJS_DIR = $(OBJS_DIR)/objs

OBJS_DIR = objs
LOGS_DIR = logfiles

INC = -Iinclude

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
DEPS = $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.d))

define ascii
		@echo "$(shell tput setaf 5)"
		@echo " ============================"
		printf " *   __ _       _           *\n"
		printf " *  / _| |_    (_)_ __ ___  *\n"
		printf " * | |_| __|   | | '__/ __| *\n"
		printf " * |  _| |_    | | | | (__  *\n"
		printf " * |_|  \__|___|_|_|  \___| *\n"
		printf " *                          *\n"
		@echo " ============================"
endef

all: $(NAME)

ascii:
	@clear
	$(call ascii)

$(NAME): $(LOGS_DIR) $(OBJS_DIR) $(OBJS)
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

$(LOGS_DIR):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating log files destination directory /$(LOGS_DIR) : "
	@mkdir -p $(LOGS_DIR)
	@echo "[OK]$(shell tput sgr0)"


$(OBJS_DIR):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR) : "
	@mkdir -p $(OBJS_DIR)
	@echo "[OK]$(shell tput sgr0)"

clean:
	@make -s ascii
	@echo -n "$(shell tput setaf 5) clean:"
	@echo -n "  Removing $(OBJS_DIR)/ directory : "
	@rm -rf $(OBJS_DIR)
	@echo "[OK]$(shell tput sgr0)"

fclean: clean
	@echo -n "$(shell tput setaf 5) fclean:"
	@echo -n " Removing executable [ $(NAME) ]: "
	@rm -rf $(NAME)
	@echo "[OK]"
	@echo -n "	 Removing $(LOGS_DIR)/ directory : "
	@rm -rf $(LOGS_DIR)
	@echo "[OK]$(shell tput sgr0)"

re: fclean all

.PHONY: all clean fclean