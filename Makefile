# Colour codes
END		=	\033[0m
GRAY 	=	\033[0;30m
RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
PURPLE	=	\033[0;35m
CYAN	=	\033[0;36m
WHITE	=	\033[0;37m
CYAN_B	=	\033[1;96m
GREEN_B	=	\033[1;92m

NAME	=	cub3D
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address
RM		=	rm -rf

# BONUS TOGGLE
BONUS = 0

SRC_D 	=	srcs/
OBJ_D 	=	objs/

SRC		=	main \
			error \
			exit/exit \
			exit/free_data \
			init/init_data \
			init/init_mlx \
			init/init_texture \
			render/raycasting \
			render/render \
			render/texture

SRCS	=	$(addprefix  $(SRC_D), $(addsuffix .c, $(SRC)))
OBJ		=	$(SRC:%.c=%.o)
OBJS	=	$(addprefix $(OBJ_D), $(addsuffix .o, $(OBJ)))

INCLUDE	=	-I includes -I libft -I mlx
MLX_LIB =	-L mlx -lmlx -framework OpenGL -framework AppKit
LIB		=	-Llibft -lft $(MLX_LIB)
LIBFT	=	libft/libft.a
MLX		=	mlx/libmlx.a

$(OBJ_D)%.o : $(SRC_D)%.c
			@mkdir -p $(OBJ_D)
			@mkdir -p $(OBJ_D)/exit
			@mkdir -p $(OBJ_D)/init
			@mkdir -p $(OBJ_D)/render
			@($(CC) $(FLAGS) -DBONUS=$(BONUS) $(INCLUDE) -c $< -o $@)

all:		$(NAME)

$(NAME):	$(MLX) $(LIBFT) $(OBJS)
			@($(CC) $(FLAGS) -DBONUS=$(BONUS) $(INCLUDE) $(OBJS) $(LIB) -o $(NAME))
			@echo "$(CYAN) [ OK ] | $(CYAN_B)cub3d$(END) $(CYAN)ready!$(END)"

bonus:
	make all BONUS=1

$(LIBFT):
			@echo "$(PURPLE) [ .. ] | Compiling libft..$(END)"
			@make -s -C libft
			@echo "$(PURPLE) [ OK ] | Libft ready!$(END)"

$(MLX):
			@make -s -C mlx
			@echo "(PURPLE) [ OK ] | Minilibx ready!$(END)"

clean:
			@make -s -C libft clean
			@make -s -C mlx clean
			@($(RM) $(OBJ_D))
			@echo "$(GREEN) [ OK ] | Objects removed!$(END)"

fclean: 	clean
			@make -s -C libft fclean
			@($(RM) $(NAME))
			@echo "$(GREEN) [ OK ] | Everything is clean!$(END)"

re: 		fclean all

reb: 		fclean bonus

.PHONY:		all clean fclean re
