NAME		=	pipex
CC			= 	cc
FLAGS		= 	-Wall -Wextra -Werror
SRC			= 	pipex.c get_next_line_utils.c get_next_line.c cleaner.c reader.c parser.c work_with_pipes.c \
ft_putstr_fd.c ft_split.c ft_strncmp.c ft_substr.c ft_strjoin.c
SRC_BONUS	= 	pipex_bonus.c reader_bonus.c get_next_line_utils.c get_next_line.c cleaner_bonus.c parser_bonus.c work_with_pipes_bonus.c \
ft_putstr_fd.c ft_split.c ft_strncmp.c ft_substr.c ft_strjoin.c
OB			=	$(SRC:.c=.o)

BONUS_SRC	=	pipex_bonus.c 

BONUS_OBJ	=	$(SRC_BONUS:.c=.o)

override TMP_OBJ ?= $(OB)

$(NAME) : $(TMP_OBJ)
		$(CC) $(FLAGS) -fsanitize=address -g $(TMP_OBJ) -o $@

all : $(NAME)

%.o : %.c get_next_line.h pipex.h Makefile
		$(CC) $(FLAGS) -c $< -o $@

bonus :
		make TMP_OBJ="$(BONUS_OBJ)" all

clean:
		rm -f $(OB) $(BONUS_OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONE: clean fclean re all bonus