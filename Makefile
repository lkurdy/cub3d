NAME			=	cub3D

CFLAGS			=	-g3 -Wall -Wextra -Werror -I/usr/include -Imlx -MMD -c
MLX				=	-Lmlx -lmlx_Linux -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o

DIR_SRC			=	src
DIR_OBJ			=	obj
MLX_OBJ			=	mlx/obj mlx/libmlx.a mlx/libmlx_Linux.a mlx/Makefile.gen

SRC				=	libft.c ft_split.c init.c parsing.c utils.c math.c display.c cub3D.c

OBJ				=	$(SRC:%.c=$(DIR_OBJ)/%.o)
DEP				=	$(SRC:%.c=$(DIR_OBJ)/%.d)

RED				=	$'\e[0;31m
GREEN			=	$'\e[32m
YELLOW			=	$'\e[33m
BOLD			=	$'\e[1m
UNDER			=	$'\e[4m
END				=	$'\e[0m

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c Makefile
					mkdir -p $(DIR_OBJ)
					echo "Compiling - ${YELLOW}${BOLD}${UNDER}./$<${END}..."
					$(CC) $(CFLAGS) $< -o $@
					echo "${GREEN}Done !${END}"

$(NAME):			$(OBJ)
					echo "Making - ${YELLOW}${BOLD}${UNDER}./mlx/${END}..."
					make --no-print-directory -C mlx 
					echo "${GREEN}Done !${END}"
					echo "Compiling - ${YELLOW}${BOLD}${UNDER}./$(NAME)${END}..."
					$(CC) $(OBJ) $(MLX) $(NAME)
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

all:				$(NAME)

clean:
					echo "Cleaning - ${RED}${BOLD}${UNDER}./mlx/${END}..."
					rm -rf $(MLX_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

fclean:
					echo "Cleaning - ${RED}${BOLD}${UNDER}./mlx/${END}..."
					rm -rf $(MLX_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(NAME)${END}..."
					rm -rf $(NAME)
					echo "${GREEN}Done !${END}"
					echo "${GREEN}${BOLD}${UNDER}Task completed successfully.${END}"

re:
					echo "Cleaning - ${RED}${BOLD}${UNDER}./mlx/${END}..."
					rm -rf $(MLX_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(DIR_OBJ)/${END}..."
					rm -rf $(DIR_OBJ)
					echo "${GREEN}Done !${END}"
					echo "Deleting - ${RED}${BOLD}${UNDER}./$(NAME)${END}..."
					rm -rf $(NAME)
					echo "${GREEN}Done !${END}"
					make --no-print-directory all

git:
					git add .
					git commit -m "$(NAME)"
					git push

-include $(DEP)

.PHONY:				all clean fclean re git
.SILENT:
