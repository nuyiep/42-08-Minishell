# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 09:10:03 by plau              #+#    #+#              #
#    Updated: 2023/01/17 17:27:10 by nchoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        	=   	minishell
LIBFT        	=    	libft.a
CC            	=    	gcc
RM            	=    	rm -f
CFLAGS       	=    	-Wall -Wextra -Werror
CFLAGS		    +=		-I/usr/local/opt/readline/include
# CFLAGS       	+=    	-fsanitize=address -g3
READLINE		=		-lreadline
READLINE		+=		-L/usr/local/opt/readline/lib
SRCS_FILES    	=   	ms_main \
						ms_cd \
						ms_pwd \
						ms_exit \
						ms_echo \
						ms_envp \
						ms_init \
						ms_unset \
						ms_error \
						ms_export \
						ms_signal \
						ms_builtins \
						ms_shell_loop \
						ms_exporthelper \
						ms_expand
SRCS       		=     	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
OBJS        	=     	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
SRCS_DIR    	=    	srcs/
LIBFT_DIR    	=    	libft/
OBJS_DIR    	=    	objs/

all:             
						mkdir -p $(OBJS_DIR)
						make libft
						make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):        $(OBJS)
				$(CC) $(CFLAGS) $^ $(READLINE) -Llibft -lft -o $@

libft:
				make -C $(LIBFT_DIR)

clean:
				rm -rf $(OBJS_DIR)
				make clean -C $(LIBFT_DIR)

fclean:         clean
				make fclean -C $(LIBFT_DIR)
				rm -rf $(NAME)

re:             fclean all

.PHONY:         all libft clean fclean re