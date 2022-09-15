NAME = gnl_test

SRC_TEST = gnl_test.c

CFLAGS = -Wall -Wextra -Werror

INCLUDES = ../src

CC = gcc

BUFFER_SIZE = BUFFER_SIZE=42

all: $(NAME)

$(NAME): $(SRC_TEST)
	$(CC) $(CFLAGS) -D$(BUFFER_SIZE) -I$(INCLUDES) $(SRC_TEST) -o $(NAME) ../src/get_next_line.c

	
