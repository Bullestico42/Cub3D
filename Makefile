NAME = cub3D

# === Dossiers ===
SRC_DIR = src/
PAR_DIR = src/parsing/
GNL_DIR = get_next_line/
OBJ_DIR = obj
INC_DIR = headers
LIBFT_DIR = libft

# === Fichiers sources ===
SRCS =  $(SRC_DIR)main.c \
                $(SRC_DIR)initialisation.c \
                $(SRC_DIR)render.c \
                $(SRC_DIR)utils.c \
                $(PAR_DIR)init.c \
                $(PAR_DIR)extract_raw_file.c \
                $(PAR_DIR)parse_map.c \
                $(PAR_DIR)extract_data.c \
                $(PAR_DIR)extract_colors.c \
                $(PAR_DIR)parse_elements.c \
                $(PAR_DIR)line_utils.c \
                $(SRC_DIR)raycasting_utils.c \
                $(SRC_DIR)minimap_background.c \
                $(SRC_DIR)minimap.c \
                $(SRC_DIR)movement.c \
                $(SRC_DIR)raycasting.c \
                $(SRC_DIR)controls.c \
                $(GNL_DIR)get_next_line.c \
                $(GNL_DIR)get_next_line_utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(GNL_DIR)/%.c=$(OBJ_DIR)/%.o)

# === Commandes ===
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -g

# === OS Detection ===
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
        MLX_DIR = mlx/mlx_linux
        MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
        MLX_INC = -I$(MLX_DIR)
else ifeq ($(UNAME_S), Darwin)
        MLX_DIR = mlx/mlx_mac
        MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
        MLX_INC = -I$(MLX_DIR)
        CFLAGS += -DGL_SILENCE_DEPRECATION
endif

# === Libft ===
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# === Mlx ===
MLX = $(MLX_DIR)/libmlx.a

# === Règles ===

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(MLX_INC) $(LIBFT_INC) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PAR_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MLX):
	@make -C $(MLX_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@make bonus -C $(LIBFT_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
