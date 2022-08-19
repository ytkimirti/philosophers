NAME = philo_bonus

# NOTE: Add -Werror here before pushing to intra
CFLAGS = -MD -Wall -Wextra -Ilibft -g
LDFLAGS =
LDLIBS =

# NOTE: You have to have libcriterion.a file in your LIBRARY_PATH and criterion.h file in C_INCLUDE_PATH
# If you installed them with homebrew, add them to these env variables in your shell config
TESTFLAGS = -lcriterion

CC = gcc
SHELL = /bin/sh

SRC_DIR = .
OBJ_DIR = obj
TEST_DIR = tests

ENTRY_SRCS = $(SRC_DIR)/main.c

# You SHALL NOT include entry srcs here.
SRCS = \
	$(SRC_DIR)/errors.c \
	$(SRC_DIR)/ft_atoi.c \
	$(SRC_DIR)/ft_isspace.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/philo.c \
	$(SRC_DIR)/semaphores.c \
	$(SRC_DIR)/util_time.c \


TEST_SRCS = 

ENTRY_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(ENTRY_SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/bin/%, $(TEST_SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(ENTRY_OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJS) $(ENTRY_OBJS) -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(TEST_DIR)/bin:
	mkdir $(TEST_DIR)/bin

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_DIR)/bin/%: $(TEST_DIR)/%.c $(OBJS) | $(TEST_DIR)/bin
	$(CC) $(CFLAGS) $(LDLIBS) $(LDFLAGS) $(TESTFLAGS) $(OBJS) $< -o $@

test: $(TEST_BINS)
	for test in $(TEST_BINS) ; do ./$$test ; done

run: all
	@# count die eat sleep [max_eat_count]
	./philo 2 3000 1000 500 3

socrates: 
	python3 ../socrates/socrates.py -n 0 ../

re: fclean all

clean:
	rm -rf $(OBJ_DIR) $(TEST_DIR)/bin

fclean: clean
	rm -f $(NAME)

.PHONY: all test run socrates re clean fclean clean

-include $(OBJ_DIR)/*.d
