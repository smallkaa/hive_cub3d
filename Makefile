# Library name
NAME = cub3D
BONUS_NAME  := cub3D_bonus

# Compiler and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I./mandatory/includes -I./bonus/includes -I./MLX42/include -Wunreachable-code -O0
DEPFLAGS = -MMD -MP
CFLAGS  += $(DEPFLAGS)

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

SRCS_PATH = ./mandatory/src
SRCS_BONUS_PATH = ./bonus/src
OBJS_PATH = ./obj
OBJS_M_PATH = $(OBJS_PATH)/mandatory
OBJS_B_PATH = $(OBJS_PATH)/bonus
LIBFT_PATH = ./libft
MLX_PATH = ./MLX42
MLX_REPO = https://github.com/codam-coding-college/MLX42.git

# Source files (explicit lists)
MLXLIB = MLX42/build/libmlx42.a
LIBFT = $(LIBFT_PATH)/libft.a

SRC = $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/raycast/raycast.c \
		$(SRCS_PATH)/raycast/drawback.c \
		$(SRCS_PATH)/raycast/drawtexture.c \
		$(SRCS_PATH)/raycast/texture_utils.c \
		$(SRCS_PATH)/init/textures.c \
		$(SRCS_PATH)/parser/utils.c \
		$(SRCS_PATH)/parser/parsing.c \
		$(SRCS_PATH)/parser/map_check.c \
		$(SRCS_PATH)/parser/bound_checker.c \
		$(SRCS_PATH)/parser/config.c \
		$(SRCS_PATH)/parser/config_utils.c \
		$(SRCS_PATH)/parser/read.c \
		$(SRCS_PATH)/game/loop.c \
		$(SRCS_PATH)/game/movement.c \
		$(SRCS_PATH)/game/game_utils.c

SRC_BONUS = $(SRCS_BONUS_PATH)/main_bonus.c \
		$(SRCS_BONUS_PATH)/raycast/raycast_bonus.c \
		$(SRCS_BONUS_PATH)/raycast/drawback_bonus.c \
		$(SRCS_BONUS_PATH)/raycast/drawtexture_bonus.c \
		$(SRCS_BONUS_PATH)/raycast/texture_utils_bonus.c \
		$(SRCS_BONUS_PATH)/init/textures_bonus.c \
		$(SRCS_BONUS_PATH)/parser/utils_bonus.c \
		$(SRCS_BONUS_PATH)/parser/parsing_bonus.c \
		$(SRCS_BONUS_PATH)/parser/map_check_bonus.c \
		$(SRCS_BONUS_PATH)/parser/bound_checker_bonus.c \
		$(SRCS_BONUS_PATH)/parser/config_bonus.c \
		$(SRCS_BONUS_PATH)/parser/config_utils_bonus.c \
		$(SRCS_BONUS_PATH)/parser/read_bonus.c \
		$(SRCS_BONUS_PATH)/game/loop_bonus.c \
		$(SRCS_BONUS_PATH)/game/movement_bonus.c \
		$(SRCS_BONUS_PATH)/game/game_utils_bonus.c

# Objects & deps split per variant
OBJ_M := $(patsubst $(SRCS_PATH)/%.c, $(OBJS_M_PATH)/%.o, $(SRC))
OBJ_B := $(patsubst $(SRCS_BONUS_PATH)/%.c, $(OBJS_B_PATH)/%.o, $(SRC_BONUS))
DEPS_M := $(OBJ_M:.o=.d)
DEPS_B := $(OBJ_B:.o=.d)

# Default: mandatory
all: $(MLX_PATH) $(NAME)

# Mandatory link
$(NAME): $(OBJ_M) $(LIBFT) $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJ_M) $(LIBFT) $(MLXLIB) $(LDFLAGS) -o $(NAME)

# Mandatory compile
$(OBJS_M_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MF $(@:.o=.d) -MT $@ -c $< -o $@

# Bonus entrypoint (does NOT rebuild mandatory)
bonus: $(MLX_PATH) $(BONUS_NAME)

# Bonus link
$(BONUS_NAME): $(OBJ_B) $(LIBFT) $(MLX_PATH)
	$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT) $(MLXLIB) $(LDFLAGS) -o $(BONUS_NAME)

# Bonus compile
$(OBJS_B_PATH)/%.o: $(SRCS_BONUS_PATH)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MF $(@:.o=.d) -MT $@ -c $< -o $@

# Clone and build MLX42
$(MLX_PATH):
	git clone $(MLX_REPO) $(MLX_PATH)
	cmake -B $(MLX_PATH)/build -S $(MLX_PATH) -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF
	cmake --build $(MLX_PATH)/build

# Build libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

# Include deps for both variants
-include $(DEPS_M) $(DEPS_B)

# Clean
clean:
	@rm -rf $(OBJS_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(MLX_PATH)/build
	@rm -f sources_dump.txt

fclean: clean
	/bin/rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -rf $(MLX_PATH)

re: fclean all

.PHONY: all bonus clean fclean re
