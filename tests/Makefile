NAME = gnl_test

SRC_TEST = gnl_test.c

CFLAGS = -Wall -Wextra -Werror

INCLUDES = ../src

CC = gcc

SRCDIR = ../src

SRC = get_next_line.c get_next_line_utils.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

BUFFER_SIZE = BUFFER_SIZE=$(B)

TEST_FILES_DIR = test_files

TEST_FILES = $(addprefix $(TEST_FILES_DIR)/, \
		a_nl.txt \
		a-k.txt)

all: $(NAME) exp
	@./$(NAME)

$(NAME): $(SRCS) $(SRC_TEST) $(TEST_FILES)
	$(CC) $(CFLAGS) -D$(BUFFER_SIZE) -I$(INCLUDES) $(SRC_TEST) -o $(NAME) $(SRCS)

m: mtest exp
	@./mtest

mtest: $(SRCS) minunit.c $(TEST_FILES)
	$(CC) $(CFLAGS) -D$(BUFFER_SIZE) -I$(INCLUDES) minunit.c -o mtest $(SRCS)

vgnl: $(NAME) exp
	valgrind ./$(NAME)

vm: mtest exp
	valgrind --error-exitcode=42 --leak-check=full ./mtest
	
exp:
	@export B

fclean:
	@rm -f $(NAME)
	@rm -f mtest

re: fclean all

rem: fclean m
