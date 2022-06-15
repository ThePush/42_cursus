NAME = ft_printf_test
SRCS = ft_printf.c	main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o:%.c
	@cc -c -w -erroff=t $< -o $@

$(NAME):$(OBJS)
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Compiling... $(shell tput sgr0)"
	@cc $(OBJS) -o $(NAME) > /dev/null
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"
	@echo "$(shell tput bold)$(shell tput setaf 2)SUCCESS Binary file \"ft_printf_test\" created$(shell tput sgr0)"

clean:
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Deleting project's object files... $(shell tput sgr0)"
	@rm -rf *.o
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"

fclean: clean
	@echo -n "$(shell tput bold)$(shell tput setaf 5)Deleting binary... $(shell tput sgr0)"
	@rm -rf $(NAME)
	@echo "$(shell tput bold)$(shell tput setaf 5)√$(shell tput sgr0)"

re: fclean all
