#------------MakeFile------------#
NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRCS_DIR = ./src/
SRCS =	main.c \
		parse.c \
		utils.c \
		routine.c \
		philo.c \
		checkthread.c \
		status.c  \

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: obj $(NAME)

obj:
	mkdir obj

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -I ./includes/ -o $@ -c $< -g

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -g

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf obj

re: fclean all

.PHONY: all clean fclean re
