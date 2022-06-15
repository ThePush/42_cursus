SERVER = server
CLIENT = client
FLAGS = -Wall -Wextra -Werror -g

SRCS_SERV = $(addprefix sources/, \
	server.c \
	)

OBJS_SERV = $(SRCS_SERV:.c=.o)

SRCS_CLIENT = $(addprefix sources/, \
	client.c \
	)

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

UTILS = $(addprefix sources/, \
	minitalk_ascii.c \
	minitalk_utils.c \
	)

OBJS_UTILS = $(UTILS:.c=.o)

LIB = ./libraries/libft/libft.a

all: $(SERVER) $(CLIENT)

LIBFT = libraries/libft/libft.a

$(LIBFT):
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Building libft... $(shell tput sgr0)"
	@make -sC libraries/libft > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"

%.o:%.c
	@cc $(FLAGS) -c $< -o $@

$(SERVER):$(OBJS_SERV) $(OBJS_UTILS) $(LIBFT)
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Compiling \"server\"... $(shell tput sgr0)"
	@cc $(FLAGS) -o $(SERVER) $(OBJS_SERV) $(OBJS_UTILS) $(LIB)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo "$(shell tput bold)$(shell tput setaf 2)SUCCESS Binary file \"server\" created$(shell tput sgr0)"

$(CLIENT):$(OBJS_CLIENT) $(OBJS_UTILS) $(LIBFT)
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Compiling \"client\"... $(shell tput sgr0)"
	@cc $(FLAGS) -o $(CLIENT) $(OBJS_CLIENT) $(OBJS_UTILS) $(LIB)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo "$(shell tput bold)$(shell tput setaf 2)SUCCESS Binary file \"client\" created$(shell tput sgr0)"

clean:
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Deleting project's objects... $(shell tput sgr0)"
	@rm -rf $(OBJS_SERV) $(OBJS_CLIENT) $(OBJS_UTILS) $(OBJS_SERV_BONUS) $(OBJS_CLIENT_BONUS) $(OBJS_UTILS_BONUS)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Deleting libft's objects... $(shell tput sgr0)"
	@make clean -sC libraries/libft > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"


fclean: clean
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Deleting binaries... $(shell tput sgr0)"
	@rm -rf $(SERVER) $(CLIENT)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Cleaning libft... $(shell tput sgr0)"
	@make fclean -sC libraries/libft > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"

re: fclean all
