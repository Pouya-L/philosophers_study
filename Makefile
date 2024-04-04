# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plashkar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 11:25:14 by plashkar          #+#    #+#              #
#    Updated: 2023/12/14 11:36:34 by plashkar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

CC = cc

STANDARD_FLAGS 	= -Wall -Werror -Wextra -g #-fsanitize=address

INCLUDE = -Iincludes

PHILO_LIB = philo.a

PHILO = philo

PHILO_SRC = src/philo.c
PHILO_OBJ = $(PHILO_SRC:.c=.o)

PHILO_BONUS = philo_bonus

PHILO_BONUS_SRC = bonus_src/philo.c
PHILO_BONUS_OBJ = $(PHILO_BONUS_SRC:.c=.o)

%.o: %.c
	@$(CC) $(STANDARD_FLAGS) -o $@ -c $<

all: $(SERVER) $(CLIENT)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(CLIENT): $(CLIENT_OBJ) $(OBJ)
	@echo "Compiling $@"
	@make -C $(LIBFT_DIR) > /dev/null
	@$(CC) $(STANDARD_FLAGS) $(INCLUDE) $(CLIENT_OBJ) $(LIBFT_A)  -o client > /dev/null
	@echo "client has been created."

$(SERVER): $(SERVER_OBJ) $(OBJ)
	@echo "Compiling $@"
	@make -C $(LIBFT_DIR) > /dev/null
	@$(CC) $(STANDARD_FLAGS) $(INCLUDE) $(SERVER_OBJ) $(LIBFT_A)  -o server > /dev/null
	@echo "server has been created."

$(CLIENT_BONUS): $(CLIENT_BONUS_OBJ) $(OBJ)
	@echo "Compiling $@"
	@make -C $(LIBFT_DIR) > /dev/null
	@$(CC) $(STANDARD_FLAGS) $(INCLUDE) $(CLIENT_BONUS_OBJ) $(LIBFT_A)  -o client_bonus > /dev/null
	@echo "client_bonus has been created."

$(SERVER_BONUS): $(SERVER_BONUS_OBJ) $(OBJ)
	@echo "Compiling $@"
	@make -C $(LIBFT_DIR) > /dev/null
	@$(CC) $(STANDARD_FLAGS) $(INCLUDE) $(SERVER_BONUS_OBJ) $(LIBFT_A)  -o server_bonus > /dev/null
	@echo "server_bonus has been created."

clean:
	@rm -f src/*.o
	@rm -f bonus_src/*.o
	@make -C $(LIBFT_DIR) clean > /dev/null
	@echo Object files have been deleted.

fclean: clean
	@rm -f $(SERVER) $(CLIENT)
	@rm -f $(SERVER_BONUS) $(CLIENT_BONUS)
	@make -C $(LIBFT_DIR) fclean > /dev/null
	@echo All created files have been deleted.

re: fclean all

.PHONY: fclean clean all re
