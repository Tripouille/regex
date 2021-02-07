CC = clang++ -Wall -Wextra -Werror -fsanitize=address
SRCS = Regex.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
all: $(OBJS)
	$(CC) $(OBJS)
	./a.out

$(OBJS): %.o: %.cpp Regex.hpp
	$(CC) -c $*.cpp

fclean clean:
	rm -f $(OBJS) a.out