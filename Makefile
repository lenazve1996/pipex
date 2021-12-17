NAME		=	pipex
CC			= 	cc
FLAGS		= 	-Wall -Wextra -Werror
SRC			= 	pipex.c get_next_line_utils.c get_next_line.c cleaner.c reader.c parser.c work_with_pipes.c
OB			=	$(SRC:.c=.o)

BONUS_SRC	=	pipex_bonus.c 

BONUS_OBJ	=	$(BONUS_SRC:.c=.o)

override TMP_OBJ ?= $(OB)

$(NAME) : $(SRC) libft/libft.h get_next_line.h pipex.h
		$(CC) $(FLAGS) $< libft.a -o $@

all : $(NAME)

#%.o : %.c libft/libft.h get_next_line.h pipex.h
#		$(CC) $(FLAGS) -c $< -o $@

#bonus :
#		@make TMP_OBJ="$(BONUS_OBJ)" all

#clean:
#		rm -f $(OB) $(BONUS_OBJ)

fclean:
		rm -f $(NAME)

re: fclean all

.PHONE: clean fclean re all bonus