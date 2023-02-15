CXX = c++

STL = -DREAL_STL

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

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re
