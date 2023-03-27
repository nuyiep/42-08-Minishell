# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nchoo <nchoo@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 09:10:03 by plau              #+#    #+#              #
#    Updated: 2023/03/27 19:59:05 by nchoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        	=   	minishell
LIBFT        	=    	libft.a
CC            	=    	gcc
RM            	=    	rm -f
CFLAGS       	=    	-Wall -Wextra -Werror
CFLAGS		    +=		-I/usr/local/opt/readline/include
# CFLAGS			+=		-I/opt/homebrew/opt/readline/include
# CFLAGS       	+=    	-fsanitize=address -g3
READLINE		=		-lreadline
READLINE		+=		-L/usr/local/opt/readline/lib
# READLINE		+=		-L/opt/homebrew/opt/readline/lib
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
						ms_expand \
						ms_expand_utils \
						ms_lexer \
						ms_lexer_utils \
						ms_free \
						ms_executor \
						ms_heredoc \
						ms_pipe \
						ms_child \
						ms_redirection \
						ms_redirection2 \
						ms_parser \
						ms_check \
						ms_variable
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
