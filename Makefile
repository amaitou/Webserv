GPP = g++
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
VFLAG = -std=c++11
NAME = webserv
SOURCE_DIR = ./sources

CPPFILES = $(wildcard $(SOURCE_DIR)/*/*.cpp) main.cpp
OBJECTS = $(CPPFILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "\033[0;32m[*] linking $@\033[0m"
	@$(GPP) $(CFLAGS) $(VFLAG) $^ -o $@

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@echo "\033[0;33m[*] compiling $<\033[0m"
	@$(GPP) $(CFLAGS) $(VFLAG) -c $< -o $@

main.o: main.cpp
	@echo "\033[0;33m[*] compiling $<\033[0m"
	@$(GPP) $(CFLAGS) $(VFLAG) -c $< -o $@

clean:
	@echo "\033[0;31m[*] cleaning from object files\033[0m"
	@rm -rf $(OBJECTS)
fclean: clean
	@echo "\033[0;31m[*] remove the executable file\033[0m"
	@rm -rf $(NAME)

run: $(NAME)
	@echo "\033[0;32m[*] running the $<\033[0m"
	@clear && ./$(NAME)

re: clean all run fclean
