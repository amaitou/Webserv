GPP = c++
CFLAGS = -Wall -Wextra -Werror
VFLAG = -std=c++11
NAME = server
CPPF = HTTP_Request.cpp TCP_Connection.cpp TCP_Exceptions.cpp ClientSide.cpp main.cpp

SRCS = $(CPPF:.cpp=.o)

all: $(NAME)

$(NAME): $(SRCS)
	$(GPP) $(VFLAG) $(CFLAGS) $^ -o $@

%.o : %.cpp
	$(GPP) $(CFLAGS) $(VFLAG) -c $^

fclean:
	rm -rf $(NAME) $(SRCS)

run:
	make && clear && ./server

re: fclean all
