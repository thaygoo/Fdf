NAME		=	fdf

SRC			=	main.c \
				parsing.c \
				parsing_utils.c \
				parsing_map.c \
				parsing_error.c \
				parsing_buffer.c \
				draw_utils2.c \
				draw.c \
				draw_utils.c \
				draw_bounds.c \
				mlx_utils.c \
				projection.c \
				projection_utils.c \
				exit_handling.c \
				init.c

OBJ			=	$(SRC:.c=.o)

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra

LXFLAGS		=	-Lresources/minilibx-linux -lmlx_Linux -lX11 -lXext -lm

LIBFTPATH	=	./resources/libft

LXPATH		=	./resources/minilibx-linux

RM			=	rm -rf

all:$(NAME)

$(NAME):$(OBJ)
	@make -s -C $(LIBFTPATH)
	@make -s -C $(LXPATH)
	@$(CC) $(CFLAGS) $(OBJ) $(LXFLAGS) ./resources/libft/libft.a -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -s -C $(LIBFTPATH) clean
	@$(RM) $(OBJ)

fclean:	clean
	@make -s -C $(LIBFTPATH) fclean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re