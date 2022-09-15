NAME = gnl_test

SRC_TEST = gnl_test.c

CFLAGS = -Wall -Wextra -Werror

INCLUDES = ../src

CC = gcc

SRCDIR = ../src

SRC = get_next_line.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

BUFFER_SIZE = BUFFER_SIZE=21

TEST_FILES_DIR = test_files
TEST_FILES = $(addprefix $(TEST_FILES_DIR)/, \
		a_nl.txt)

all: $(NAME)

$(NAME): $(SRCS) $(SRC_TEST) $(TEST_FILES)
	@$(CC) $(CFLAGS) -D$(BUFFER_SIZE) -I$(INCLUDES) $(SRC_TEST) -o $(NAME) $(SRCS)
	@./$(NAME)
	
fclean:
	rm -f $(NAME)

re: fclean all
