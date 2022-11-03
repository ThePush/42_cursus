NAME = minishell
FLAGS = -Wall -Wextra -Werror -g3

SRCS = builtins_cmd.c \
	   builtins_core.c \
	   builtins_env.c \
	   builtins_env_utils.c \
	   builtins_utils.c \
	   create_list.c \
	   environment_handler.c \
	   errors.c \
	   exec_cmd.c \
	   expand_path.c \
	   expand_vars.c \
	   fd_redir_handler.c \
	   fork_cmd.c \
	   free_memory.c \
	   ft_input_split.c \
	   ft_symsplit.c \
	   here_doc.c \
	   init_prompt_utils.c \
	   main.c \
	   parsing.c \
	   quotes_trim.c \
	   signal_handler.c \
	   fd_redir_handler_utils.c \

SRCS_DIR = srcs

OBJS_DIR = obj

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

LIB = ./libft/libft.a

INC = includes/minishell.h

LIBFT = libft/libft.a

define ascii
		@echo "$(shell tput setaf 5)"
		@echo "============================================"
		printf "*            _       _     _          _ _  *\n"
		printf "*  _ __ ___ (_)_ __ (_)___| |__   ___| | | *\n"
		printf "* | '_ \` _ \| | '_ \| / __| '_ \ / _ \ | | *\n"
		printf "* | | | | | | | | | | \__ \ | | |  __/ | | *\n"
		printf "* |_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_| *\n"
		printf "*                        A 42Paris project *\n"
		@echo "============================================"
endef

all: $(NAME)

ascii:
	@clear
	$(call ascii)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT) $(INC)
	@make -s ascii
	@make -s norminette
	@echo -n "$(shell tput setaf 5) Compiling binary : $(shell tput sgr0)"
	@cc $(FLAGS) $(OBJS) $(LIB) -lreadline -o $(NAME)
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@cc $(FLAGS) -c $< -o $@

$(LIBFT):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) Building libft : $(shell tput sgr0)"
	@make -sC libft > /dev/null
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

norminette:
	@if norminette $(SRCS) $(INC) ./libft > /dev/null; then\
        echo "$(shell tput setaf 5) Norminette : [OK]$(shell tput sgr0)";\
    else\
        echo "$(shell tput setaf 5) Norminette : $(shell tput setaf 1)[KO]$(shell tput sgr0)";\
    fi
	@sleep 0.2

clean:
	@make -s ascii
	@sleep 0.2
	@echo -n "$(shell tput setaf 5) Deleting project's objects : $(shell tput sgr0)"
	@rm -rf $(OBJS_DIR)
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2
	@echo -n "$(shell tput setaf 5) Deleting libft's objects : $(shell tput sgr0)"
	@make clean -sC libft > /dev/null
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

fclean: clean
	@echo -n "$(shell tput setaf 5) Deleting binary : $(shell tput sgr0)"
	@rm -rf $(NAME)
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2
	@echo -n "$(shell tput setaf 5) Cleaning libft : $(shell tput sgr0)"
	@make fclean -sC libft > /dev/null
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

re: fclean all
