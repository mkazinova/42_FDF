NAME = fdf

FLAGS = -Wall -Wextra -Werror -g

INC_DIR = ./libft/
OBJ_DIR = ./obj/
LIB_DIR = ./libft/
MLX_DIR = ./minilibx_macos/

SRC = main.c get_next_line_single_fd.c error_clear.c fdf_parser.c visualizer.c \
		draw.c calculations.c mouse.c expose_hook.c check_input.c
OBJ = $(addprefix $(OBJ_DIR),$(OBJ_NAMES))
OBJ_NAMES = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -lm -L $(LIB_DIR) -lft  -L $(MLX_DIR) -lmlx  -framework OpenGL -framework AppKit

$(OBJ_DIR)%.o:%.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -I $(INC_DIR) -I $(MLX_DIR) -o $@ -c $<

clean:
	make -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all
