NAME = so_long
BONUS = so_long_bonus
FLAGS = -Wall -Wextra -Werror -g

SRCS =  $(addprefix sources/srcs/, \
	so_long.c \
	moves.c \
	matrix_creation.c \
	map_checkers.c \
	hooks.c \
	game_load.c \
	game_init.c \
	cleaner.c \
	so_long_ascii.c \
	)

OBJS_SRCS = $(SRCS:.c=.o)

SRCS_BONUS = $(addprefix sources/srcs_bonus/, \
	so_long_bonus.c \
	moves_bonus.c \
	frames_bonus.c \
	matrix_creation_bonus.c \
	map_checkers_bonus.c \
	hooks_bonus.c \
	game_load_bonus.c \
	game_init_bonus.c \
	cleaner_bonus.c \
	so_long_ascii_bonus.c \
	)

OBJS_SRCS_BONUS = $(SRCS_BONUS:.c=.o)

LIB = ./libraries/libft/libft.a ./libraries/minilibx/libmlx.a -lXext -lX11 -lm

LIBFT = ./libraries/libft/libft.a

all: $(NAME)

$(LIBFT):
	@echo  -n "$(shell tput bold)$(shell tput setaf 5)Building libft... $(shell tput sgr0)"
	@make -sC libraries/libft > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	
MLX = ./libraries/minilibx/libmlx.a

$(MLX):
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Building minilibx... $(shell tput sgr0)"
	@make -sC libraries/minilibx > /dev/null 2> /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"

%.o:%.c
	@cc $(FLAGS) -c $< -o $@

$(NAME):$(OBJS_SRCS) $(LIBFT) $(MLX)
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Compiling \"so_long\"... $(shell tput sgr0)"
	@cc $(FLAGS) -o $(NAME) $(OBJS_SRCS) $(LIB)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo "$(shell tput bold)$(shell tput setaf 2)SUCCESS Binary file \"so_long\" created$(shell tput sgr0)"

bonus: $(BONUS)

$(BONUS):$(OBJS_SRCS_BONUS) $(LIBFT) $(MLX)
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Compiling \"so_long_bonus\"... $(shell tput sgr0)"
	@cc $(FLAGS) -o $(BONUS) $(OBJS_SRCS_BONUS) $(LIB)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo "$(shell tput bold)$(shell tput setaf 2)SUCCESS Binary file \"so_long_bonus\" created$(shell tput sgr0)"

clean:
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Deleting project's object files... $(shell tput sgr0)"
	@rm -rf $(OBJS_SRCS) $(OBJS_SRCS_BONUS)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Cleaning minilibx... $(shell tput sgr0)"
	@make clean -sC libraries/minilibx > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"

fclean: clean
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Deleting binary \"so_long\"... $(shell tput sgr0)"
	@rm -rf $(NAME)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Deleting binary \"so_long_bonus\"... $(shell tput sgr0)"
	@rm -rf $(BONUS)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Cleaning libft... $(shell tput sgr0)"
	@make fclean -sC libraries/libft > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"

re: fclean all
