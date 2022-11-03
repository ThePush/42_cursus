# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsemel <jsemel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 14:49:36 by dpaccagn          #+#    #+#              #
#    Updated: 2022/04/26 12:57:29 by jsemel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define compiling
	@printf '$(shell tput setaf 69)Compiling$(shell tput sgr0) %s\n' $1
	@$(CC) $(CFLAGS) -c $1 -o $2
endef

define removing
	@printf '$(shell tput setaf 59)Removing$(shell tput sgr0) %s\n' $1
	@$(RM) $1 > /dev/null
endef

SRCS		=	$(addprefix srcs/, \
				ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strdup.c \
				ft_atoi.c \
				ft_strnstr.c \
				ft_calloc.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c\
				ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c\
				ft_2d_arr_len.c\
				ft_free_2d_array.c\
				ft_put_2darr_fd.c\
				ft_extend_2d_arr.c\
				ft_arr_replace_in.c\
				ft_dup_2d_array.c\
				ft_strchars_i.c\
				ft_strchr_i.c\
				ft_subsplit.c\
				ft_isspace.c\
				ft_atoi2.c\
				ft_str_alnum.c \
				ft_str_check_var.c \
				ft_pop_charset.c \
				get_next_line.c \
				)

OBJS		= $(SRCS:.c=.o)

INC			= includes/libft.h

NAME		= libft.a

RM			= rm -f

CC			= cc

CFLAGS		= -c -Wall -Wextra -Werror -Iincludes

%.o : %.c
			$(call compiling,$<,$(<:.c=.o),0)

${NAME}:	$(OBJS) $(INC)
			@printf '$(shell tput setaf 29)Finished Compiling √ %s\n$(shell tput sgr0)' $1
			@printf '$(shell tput setaf 69)Linking objs...\n$(shell tput sgr0)'
			ar rcsv $@ $?
			@printf '$(shell tput setaf 29)Finished linking √ %s\n$(shell tput sgr0)' $1
			@make -s norminette

norminette:
			@if norminette $(SRCS) $(INC) >/dev/null; then\
				echo "$(shell tput setaf 35)Norminette check √$(shell tput sgr0)";\
			else\
				echo "$(shell tput setaf 1)Norminette check ✕$(shell tput sgr0)";\
			fi

all:		$(NAME)

clean:
			$(call removing,$(OBJS) $(BONUS_OBJS))

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: re clean fclean

