NAME = gnl_test

SRC_TEST = gnl_test.c

CFLAGS = -Wall -Wextra -Werror

INCLUDES = ../src

CC = gcc

SRCDIR = ../src

SRC = get_next_line.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

BUFFER_SIZE = BUFFER_SIZE=$(B)

TEST_FILES_DIR = test_files

TEST_FILES = $(addprefix $(TEST_FILES_DIR)/, \
		a_nl.txt \
		a-k.txt)

all: $(NAME)
	@./$(NAME)

$(NAME): $(SRCS) $(SRC_TEST) $(TEST_FILES)
	@$(CC) $(CFLAGS) -D$(BUFFER_SIZE) -I$(INCLUDES) $(SRC_TEST) -o $(NAME) $(SRCS)

m: mtest 
	@./mtest

mtest: $(SRCS) minunit.c $(TEST_FILES)
	@$(CC) $(CFLAGS) -D$(BUFFER_SIZE) -I$(INCLUDES) minunit.c -o mtest $(SRCS)

vgnl: $(NAME)
	valgrind ./$(NAME)

vm: mtest
	valgrind ./mtest
	
fclean:
	@rm -f $(NAME)

re: fclean all
