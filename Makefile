# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmelo-ca <dmelo-ca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 17:03:47 by dmelo-ca          #+#    #+#              #
#    Updated: 2025/02/25 17:03:48 by dmelo-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += -s

CC = cc
FLAGS = -Wall -Wextra -Werror
INCFLAGS = -lpthread
OBJS = $(SRCS:.c=.o)
SRCS = main.c aux_funcs.c init.c thread_funcs.c states.c get.c sync.c free.c time.c parse.c
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
NC = \033[0m

all: philo

philo: $(OBJS)
	@echo "# $(GREEN)Building project...$(NC)"
	@$(CC) -g -O0 -o philo $(OBJS) $(FLAGS) $(INCFLAGS) && echo "$(GREEN)Done!$(NC)"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f *.o
	@echo "# $(YELLOW)Cleaning...$(NC)"

fclean: clean
	@rm -f philo
	@echo "# $(RED)Fully Cleaned!$(NC)"

re: fclean all

.PHONY: all clean fclean re
