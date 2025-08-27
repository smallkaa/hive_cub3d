
# Library name
NAME = cub3D
# Compiler and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I./includes/ -I./MLX42/include -Wunreachable-code -O0

# --- OS Specific Configuration ---
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	# Flags for Linux
	LDFLAGS = -ldl -lglfw -lm
else ifeq ($(UNAME_S),Darwin)
	# Flags for macOS
	# Check for Homebrew and GLFW dependency
	BREW_PATH := $(shell which brew)
	ifeq ($(BREW_PATH),)
		$(error "Homebrew not found. Please install it from https://brew.sh/")
	endif
	GLFW_PREFIX := $(shell brew --prefix glfw 2>/dev/null)
	ifeq ($(GLFW_PREFIX),)
		$(error "GLFW library not found. Please install it by running: brew install glfw")
	endif
	LDFLAGS = -L$(GLFW_PREFIX)/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif
# --- End of OS Specific Configuration ---

SRCS_PATH = ./src
OBJS_PATH = ./obj
LIBFT_PATH = ./libft
MLX_PATH = ./MLX42
MLX_REPO = https://github.com/codam-coding-college/MLX42.git

# Source files and object files
MLXLIB = MLX42/build/libmlx42.a
LIBFT = $(LIBFT_PATH)/libft.a
SRC = $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/raycast/raycast.c \
		$(SRCS_PATH)/raycast/drawback.c \
		$(SRCS_PATH)/raycast/drawtexture.c \
        $(SRCS_PATH)/raycast/texture_utils.c \
		$(SRCS_PATH)/init/keys_init.c \
		$(SRCS_PATH)/init/mlx_init.c \
		$(SRCS_PATH)/init/textures.c \
		$(SRCS_PATH)/parser/utils.c \
		$(SRCS_PATH)/parser/parsing.c \
		$(SRCS_PATH)/parser/map_check.c \
		$(SRCS_PATH)/parser/config.c \
		$(SRCS_PATH)/parser/read.c \
		$(SRCS_PATH)/map_utils/bound_checker.c \
		$(SRCS_PATH)/map_utils/print_map.c \
		$(SRCS_PATH)/game/loop.c \
		$(SRCS_PATH)/game/movement.c \
		$(SRCS_PATH)/game/game_utils.c \


OBJ := $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(SRC))

# Default rule to create the library
all: $(MLX_PATH) $(NAME)

# Rule to create the library from object files
$(NAME): $(OBJ) $(LIBFT) $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXLIB) $(LDFLAGS) -o $(NAME)

# Compile each .c file into a .o file
$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $< -o $@

#Clone and build MLX42
$(MLX_PATH):
	git clone $(MLX_REPO) $(MLX_PATH)
	cmake -B $(MLX_PATH)/build -S $(MLX_PATH) -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF
	cmake --build $(MLX_PATH)/build

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

# Clean rule to remove object files
clean:
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean
#	@rm -rf $(MLX_PATH)/build
	@rm -f sources_dump.txt

fclean: clean
	/bin/rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
#	@rm -rf $(MLX_PATH)

re: fclean all

.PHONY: all clean fclean re
DEPFLAGS = -MMD -MP
CFLAGS  += $(DEPFLAGS)
DEPS := $(OBJ:.o=.d)

-include $(DEPS)