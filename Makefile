GPP = g++
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = webserv
SOURCE_DIR = ./sources
HF = ./includes/*.hpp

CPPFILES = $(wildcard $(SOURCE_DIR)/*/*.cpp) $(wildcard $(SOURCE_DIR)/main.cpp)
OBJECTS = $(CPPFILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "\033[0;32m[*] linking $@\033[0m"
	@$(GPP) $(CFLAGS) $^ -o $@

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.cpp  $(HF)
	@echo "\033[0;33m[*] compiling $<\033[0m"
	@$(GPP) $(CFLAGS) -c $< -o $@

main.o: main.cpp  ../includes/*.hpp
	@echo "\033[0;33m[*] compiling $<\033[0m"
	@$(GPP) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31m[*] cleaning from object files\033[0m"
	@rm -rf $(OBJECTS)
fclean: clean
	@echo "\033[0;31m[*] remove the executable file\033[0m"
	@rm -rf $(NAME)

run: $(NAME)
	@echo "\033[0;32m[*] running the $<\033[0m"
	@clear && make clean &&  ./$(NAME) ~/Desktop/Config_File/webserv.config

re: clean all run
