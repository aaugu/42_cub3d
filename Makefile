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
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

SRC_D 	=	srcs/
OBJ_D 	=	objs/

SRC		=	main
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
			@($(CC) $(FLAGS) $(INCLUDE) -c $< -o $@)

all:		$(NAME)

$(NAME):	$(MLX) $(LIBFT) $(OBJS)
			@($(CC) $(FLAGS) $(INCLUDE) $(OBJS) $(LIB) -o $(NAME))
			@echo "$(CYAN) [ OK ] | $(CYAN_B)cub3d$(END) $(CYAN)ready!$(END)"

bonus:		$(NAME)

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
