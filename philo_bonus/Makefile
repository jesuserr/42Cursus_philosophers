# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 15:04:09 by jesuserr          #+#    #+#              #
#    Updated: 2023/08/08 15:04:09 by jesuserr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo/philo
NAME_BONUS = philo_bonus

SRCS =	philo/main.c philo/errors.c philo/utils.c philo/inits.c \
		philo/routine.c philo/monitor.c
SRCS_BONUS = main_bonus.c errors_bonus.c \
			 utils_bonus.c inits_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)

INCLUDE = -I ./
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -pthread

NORM = ${SRCS} philo/philo.h
NORMB = ${SRCS_BONUS} philo_bonus/philo_bonus.h
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