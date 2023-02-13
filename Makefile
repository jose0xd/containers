CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

NAME = main

all: $(NAME)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

test-utils: tests/test_utilities.cpp
	$(CXX) $(CXXFLAGS) tests/test_utilities.cpp -o ft-utils
	$(CXX) -Wall -Wextra -Werror tests/test_utilities.cpp -DREAL_STL -o std-utils
	./ft-utils > ft.out
	./std-utils > std.out
	vimdiff ft.out std.out

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re
