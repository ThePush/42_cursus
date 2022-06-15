NAME = push_swap
FLAGS = -Wall -Wextra -Werror -g

SRCS = $(addprefix sources/, \
	   check_args.c \
	   execute.c \
	   load_stack.c \
	   ra_rb_rr.c \
	   selection_sort.c \
	   get_extremes.c \
	   pa_pb.c \
	   rra_rrb_rrr.c \
	   sort_2_3_elems.c \
	   is_stack_sorted.c \
	   main.c \
	   sa_sb_ss.c \
	   radix_sort.c \
	   ft_perror.c \
	   )

OBJS = $(SRCS:.c=.o)

LIB = ./libft/libft.a

INC = includes/push_swap.h

LIBFT = libft/libft.a

define ascii
		@echo "$(shell tput setaf 5)"
		@echo " ======================================================="
		@echo " *                  _                                  *"
		@echo " *  _ __  _   _ ___| |__      _____      ____ _ _ __   *"
		@echo " * | '_ \| | | / __| '_ \    / __\ \ /\ / / _\` | '_ \\  *"
		@echo " * | |_) | |_| \__ \ | | |   \__ \^ V  V / (_| | |_) | *"
		@echo " * | .__/ \__,_|___/_| |_|___|___/ \_/\_/ \__,_| .__/  *"
		@echo " * |_|                        A 42Paris project|_|     *"
		@echo " *                                       by jsemel     *"
		@echo " ======================================================="
endef

all: $(NAME) 

ascii:
	@clear
	$(call ascii)

$(LIBFT):
	@make -s ascii
	@echo -n "$(shell tput setaf 5) Building libft : $(shell tput sgr0)"
	@make bonus -sC libft > /dev/null
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

%.o:%.c
	@cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(INC)
	@make -s ascii
	@make -s norminette
	@echo -n "$(shell tput setaf 5) Compiling binary : $(shell tput sgr0)"
	@cc $(FLAGS) -o $(NAME) $(OBJS) $(LIB)
	@echo "$(shell tput setaf 5)[OK]$(shell tput sgr0)"
	@sleep 0.2

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
	@echo -n "$(shell tput setaf 5) Deleting objects : $(shell tput sgr0)"
	@rm -rf $(OBJS)
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
