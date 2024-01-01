# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/06 11:57:51 by rlabbiz           #+#    #+#              #
#    Updated: 2023/12/17 10:51:26 by rlabbiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C++			= c++
FLAGS		= -Wall -Wextra -Werror -std=c++98
NAME 		= webserv
OBJ			= main.o parser/Config.o
DFS			= main.hpp parser/Config.hpp

%.o: %.cpp $(DFS)
	$(C++) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJ)
	$(C++) $(FLAGS) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
