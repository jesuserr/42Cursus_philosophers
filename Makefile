# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/24 15:10:16 by jesuserr          #+#    #+#              #
#    Updated: 2023/04/24 15:10:16 by jesuserr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_BONUS = checker/checker

SRCS = main.c errors.c lists.c moves.c sort.c sort_utils_1.c \
sort_utils_2.c utils.c

SRCS_BONUS = checker/main.c checker/checker_utils.c checker/errors.c \
checker/get_next_line.c checker/get_next_line_utils.c \
checker/lists.c checker/moves_1.c checker/moves_2.c \
checker/sort_utils.c checker/utils.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)

INCLUDE = -I ./
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

NORM = ${SRCS} push_swap.h
NORMB = ${SRCS_BONUS} checker/get_next_line.h checker/checker.h
GREEN = "\033[0;92m"
RED = "\033[0;91m"
BLUE = "\033[0;94m"
NC = "\033[37m"

%.o: %.c
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
-include $(DEPS)

bonus: $(NAME_BONUS)
	
$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $@
-include $(DEPS_BONUS)

clean:
	$(RM) $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)
		
fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

norm:
	@echo ${BLUE}"\nChecking Norminette..."${NC}
	@if norminette $(NORM); then echo ${GREEN}"Norminette OK!\n"${NC}; \
	else echo ${RED}"Norminette KO!\n"${NC}; \
	fi

normb:
	@echo ${BLUE}"\nChecking Norminette..."${NC}
	@if norminette $(NORMB); then echo ${GREEN}"Norminette OK!\n"${NC}; \
	else echo ${RED}"Norminette KO!\n"${NC}; \
	fi

re: fclean all

.PHONY: all clean fclean re bonus norm normb