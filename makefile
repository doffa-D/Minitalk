# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 17:14:17 by hdagdagu          #+#    #+#              #
#    Updated: 2022/12/20 18:48:14 by hdagdagu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCserver = server.c \
			ft_utils.c \

SRCclient = client.c \
			ft_utils.c \

CC = gcc
FLAGS = -Wall -Werror -Wextra

client = client
server = server

OBJclient = $(SRCclient:.c=.o)
OBJserver = $(SRCserver:.c=.o)

lb_server = server_bonus.c \
			ft_utils.c \

lb_client = client_bonus.c \
			ft_utils.c \

bonus_OBJserver = $(lb_server:.c=.o)
bonus_OBJclient = $(lb_client:.c=.o)

LIBFT = libft
FT_PRINTF = ft_printf


%.o:%.c
	@$(CC) $(Flags) -c $^ -o $@ 


color =\033[0;35m

define SO_LONG

            ██            ██    ▄           ▀██  ▀██      
▄▄ ▄▄ ▄▄   ▄▄▄  ▄▄ ▄▄▄   ▄▄▄  ▄██▄   ▄▄▄▄    ██   ██  ▄▄  
 ██ ██ ██   ██   ██  ██   ██   ██   ▀▀ ▄██   ██   ██ ▄▀   
 ██ ██ ██   ██   ██  ██   ██   ██   ▄█▀ ██   ██   ██▀█▄   
▄██ ██ ██▄ ▄██▄ ▄██▄ ██▄ ▄██▄  ▀█▄▀ ▀█▄▄▀█▀ ▄██▄ ▄██▄ ██▄ 
                      
						 
endef
export SO_LONG

all	:$(OBJclient) $(OBJserver) 
	@make -C $(LIBFT)
	@make -C $(FT_PRINTF)
	@rm libft/*.o
	@rm ft_printf/*.o
	@$(CC) $(OBJclient) $(FLAGS) libs/libft.a libs/libftprintf.a -o $(client)
	@$(CC) $(OBJserver) $(FLAGS) libs/libft.a libs/libftprintf.a -o $(server)
	@echo "$(color) $$SO_LONG"


bonus:$(bonus_OBJserver) $(bonus_OBJclient)
	@make -C $(LIBFT)
	@make -C $(FT_PRINTF)
	@rm libft/*.o
	@rm ft_printf/*.o
	@$(CC) $(bonus_OBJserver) $(CFLAGS) libs/libft.a libs/libftprintf.a -o $(server)
	@$(CC) $(bonus_OBJclient) $(CFLAGS)  libs/libft.a libs/libftprintf.a -o $(client)
	@echo "$(color) $$SO_LONG"

fclean:
	@make fclean -C $(LIBFT)
	@make fclean -C $(FT_PRINTF)
	@rm -rf $(server) $(client) $(OBJserver) $(OBJclient) $(bonus_OBJserver) $(bonus_OBJclient)
clean:
	@make clean -C $(LIBFT)
	@make clean -C $(FT_PRINTF)
	@rm -rf $(OBJserver) $(OBJclient) $(bonus_OBJserver) $(bonus_OBJclient)

re:fclean all 
