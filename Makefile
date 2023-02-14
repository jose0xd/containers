CXX = c++

STL = REAL_STL

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = tests.cpp \
	tests/test_utilities.cpp \
	tests/test_iterators.cpp \
	tests/test_vector.cpp \
	tests/test_stack.cpp \
	tests/test_map.cpp \
	tests/test_set.cpp

OBJ = $(SRC:.cpp=.o)

NAME = do_tests

all: $(NAME)

%.o: %.cpp %.hpp
	mkdir -p obj/tests
	$(CXX) $(CXXFLAGS) -c $< -o obj/$@

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
