CC = clang++ -Wall -Wextra -Werror
SRCS = Regex.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
all: $(OBJS)
	@$(CC) $(OBJS)
	./a.out

$(OBJS): %.o: %.cpp
	@$(CC) -c $*.cpp

fclean clean:
	rm -f $(OBJS) a.out