NAME_FT =  ft_containers
NAME_STD =  std_containers
NAME_TESTER = ft_container_tester
NAME_42_FT = subject_ft
NAME_42_STD = subject_std

FLAGS = -std=c++98 -MMD -Wall -Wextra -Werror# -g3
CC = c++

SRCS = main.cpp
SRCS_TESTER = tester.cpp
SRCS_42_TESTER = main.cpp

SRCS_DIR = sources/mandatory
SRCS_TESTER_DIR = sources/tester
SRCS_42_TESTER_DIR = sources/subject_main

OBJS_DIR_FT = $(OBJS_DIR)/obj_ft
OBJS_DIR_STD = $(OBJS_DIR)/obj_std
OBJS_DIR_TESTER = $(OBJS_DIR)/obj_tester
OBJS_DIR_42_TESTER_FT = $(OBJS_DIR)/obj_subject_main_ft
OBJS_DIR_42_TESTER_STD = $(OBJS_DIR)/obj_subject_main_std

OBJS_DIR = objects
LOGS_DIR = logfiles

INC = -Iinclude

OBJS_FT = $(addprefix $(OBJS_DIR_FT)/, $(SRCS:.cpp=.o))
OBJS_STD = $(addprefix $(OBJS_DIR_STD)/, $(SRCS:.cpp=.o))
OBJS_TESTER = $(addprefix $(OBJS_DIR_TESTER)/, $(SRCS_TESTER:.cpp=.o))
OBJS_42_TESTER_FT = $(addprefix $(OBJS_DIR_42_TESTER_FT)/, $(SRCS_42_TESTER:.cpp=.o))
OBJS_42_TESTER_STD = $(addprefix $(OBJS_DIR_42_TESTER_STD)/, $(SRCS_42_TESTER:.cpp=.o))



DEPS_FT = $(addprefix $(OBJS_DIR_FT)/, $(SRCS:.cpp=.d))
DEPS_STD = $(addprefix $(OBJS_DIR_STD)/, $(SRCS:.cpp=.d))
DEPS_TESTER = $(addprefix $(OBJS_DIR_TESTER)/, $(SRCS_TESTER:.cpp=.d))
DEPS_42_TESTER_FT = $(addprefix $(OBJS_DIR_42_TESTER_FT)/, $(SRCS_42_TESTER:.cpp=.d))
DEPS_42_TESTER_STD = $(addprefix $(OBJS_DIR_42_TESTER_STD)/, $(SRCS_42_TESTER:.cpp=.d))

define ascii
		@echo "$(shell tput setaf 5)"
		@echo "==============================================================="
		printf "*   __ _                      _        _                      *\n"
		printf "*  / _| |_     ___ ___  _ __ | |_ __ _(_)_ __   ___ _ __ ___  *\n"
		printf "* | |_| __|   / __/ _ \| '_ \| __/ _\` | | '_ \ / _ \ '__/ __| *\n"
		printf "* |  _| |_   | (_| (_) | | | | || (_| | | | | |  __/ |  \__ \ *\n"
		printf "* |_|  \__|___\___\___/|_| |_|\__\__,_|_|_| |_|\___|_|  |___/ *\n"
		printf "*                                                             *\n"
		@echo "==============================================================="
endef

all: $(NAME_FT) $(NAME_STD) $(NAME_TESTER) $(NAME_42_FT) $(NAME_42_STD)

ascii:
	@clear
	$(call ascii)

$(NAME_FT): $(LOGS_DIR) $(OBJS_DIR_FT) $(OBJS_FT)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_FT) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_FT) $(OBJS_FT) 
	@echo "[OK]$(shell tput sgr0)"

$(NAME_STD): $(OBJS_DIR_STD) $(OBJS_STD)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_STD) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_STD) $(OBJS_STD) 
	@echo "[OK]$(shell tput sgr0)"

$(NAME_TESTER): $(OBJS_DIR_TESTER) $(OBJS_TESTER)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_TESTER) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_TESTER) $(OBJS_TESTER) 
	@echo "[OK]$(shell tput sgr0)"

$(NAME_42_FT): $(OBJS_DIR_42_TESTER_FT) $(OBJS_42_TESTER_FT)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_42_FT) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_42_FT) $(OBJS_42_TESTER_FT)
	@echo "[OK]$(shell tput sgr0)"

$(NAME_42_STD): $(OBJS_DIR_42_TESTER_STD) $(OBJS_42_TESTER_STD)
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Compiling executable [ $(NAME_42_STD) ] : "
	@$(CC) $(FLAGS) $(INC) -o $(NAME_42_STD) $(OBJS_42_TESTER_STD)
	@echo "[OK]$(shell tput sgr0)"

-include $(DEPS_FT) $(DEPS_STD) $(DEPS_TESTER) $(DEPS_42_TESTER) $(DEPS_42_TESTER_STD)

$(OBJS_DIR_FT)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_STD)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -D=STD -o $@
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_TESTER)/%.o: $(SRCS_TESTER_DIR)/%.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_42_TESTER_FT)/%.o: $(SRCS_42_TESTER_DIR)/%.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -o $@
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_42_TESTER_STD)/%.o: $(SRCS_42_TESTER_DIR)/%.cpp Makefile
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Generating object files $@ from $< : "
	@$(CC) $(FLAGS) $(INC) -c $< -D=STD -o $@
	@echo "[OK]$(shell tput sgr0)"

$(LOGS_DIR):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(LOGS_DIR) : "
	@mkdir -p $(LOGS_DIR)
	@echo "[OK]$(shell tput sgr0)"


$(OBJS_DIR_FT):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR_FT) : "
	@mkdir -p $(OBJS_DIR_FT)
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_STD):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR_STD) : "
	@mkdir -p $(OBJS_DIR_STD)
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_TESTER):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR_TESTER) : "
	@mkdir -p $(OBJS_DIR_TESTER)
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_42_TESTER_FT):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR_42_TESTER) : "
	@mkdir -p $(OBJS_DIR_42_TESTER_FT)
	@echo "[OK]$(shell tput sgr0)"

$(OBJS_DIR_42_TESTER_STD):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) make:"
	@echo -n " Creating objects destination directory /$(OBJS_DIR_42_TESTER) : "
	@mkdir -p $(OBJS_DIR_42_TESTER_STD)
	@echo "[OK]$(shell tput sgr0)"

clean:
	@make -s ascii
	@echo -n "$(shell tput setaf 5) clean:"
	@echo -n "  Removing $(OBJS_DIR)/ directory : "
	@rm -rf $(OBJS_DIR)
	@echo "[OK]$(shell tput sgr0)"

fclean: clean
	@echo -n "$(shell tput setaf 5) fclean:"
	@echo -n " Removing executable [ $(NAME_FT) ]: "
	@rm -rf $(NAME_FT)
	@echo "[OK]"
	@echo -n "	 Removing executable [ $(NAME_STD) ]: "
	@rm -rf $(NAME_STD)
	@echo "[OK]"
	@echo -n "	 Removing executable [ $(NAME_TESTER) ]: "
	@rm -rf $(NAME_TESTER)
	@echo "[OK]"
	@echo -n "	 Removing executable [ $(NAME_42_FT) ]: "
	@rm -rf $(NAME_42_FT)
	@echo "[OK]"
	@echo -n "	 Removing executable [ $(NAME_42_STD) ]: "
	@rm -rf $(NAME_42_STD)
	@echo "[OK]"
	@echo -n "	 Removing $(LOGS_DIR)/ directory : "
	@rm -rf $(LOGS_DIR)
	@echo "[OK]$(shell tput sgr0)"

re: fclean all

.PHONY: all clean fclean