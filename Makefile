NAME = ft_strace

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = main.c \
		errno_names.c \
		fatal.c \
		print.c \
		print_arg.c \
		parse.c \
		signals.c \
		syscall.c

INC = errno_names.h \
		fatal.h \
		signals.h \
		strace.h \
		syscall.h

OBJ := $(SRC:%.c=./$(OBJ_DIR)/%.o)
SRC := $(SRC:%=./$(SRC_DIR)/%)

INC := $(INC:%=./$(INC_DIR)/%)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) | $(OBJ_DIR)
	$(CC) $(FLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $^ -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(OBJ) $(NAME)

re: fclean
	$(MAKE)
