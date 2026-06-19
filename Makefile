# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 17:50:20 by maalwis           #+#    #+#              #
#    Updated: 2026/06/19 13:24:01 by maalwis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

GREEN = \033[1;92m
RED = \033[1;91m
YELLOW = \033[1;93m
BLUE = \033[1;96m
RESET = \033[0m

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	# macOS
	READLINE_FLAGS := -I$(shell brew --prefix readline)/include
	LDFLAGS := -L$(shell brew --prefix readline)/lib -lreadline
else
	# Linux
	READLINE_FLAGS :=
	LDFLAGS := -lreadline
endif

OBJ_DIR = object_files

SRC = \
	env/expansions.c \
	env/expansions_utils.c \
	env/env_utils.c \
	env/expand.c \
	env/size.c \
	exec/find_path.c \
	exec/heredoc.c \
	exec/heredoc_utils.c \
	exec/handle_heredoc.c \
	exec/infinite_pipes.c \
	exec/child_process.c \
	exec/pipes_utils.c \
	signals/signals.c \
	signals/signal_heredoc.c \
	parser/tokenizer.c \
	parser/tokenizer_utils.c \
	parser/utils.c \
	parser/free.c \
	parser/identify_token.c \
	parser/handle_quotes.c \
	main/main.c \
	main/main_utils.c \
	main/handle_redirections.c \
	builtins/cd.c \
	builtins/pwd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/export.c \
	builtins/export_utils.c \
	builtins/unset.c \
	builtins/exit.c \
	builtins/builtins.c

LIBFT_PATH = superlibft
LIBFT = $(LIBFT_PATH)/libft.a

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(OBJ_DIR) $(NAME)
	@printf " $(GREEN)✅ Compilation terminée avec succès$(RESET)\n"

$(NAME): $(OBJ) $(LIBFT)
	@printf " $(BLUE)🔗 Liaison des objets$(RESET)\n"
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@printf " $(GREEN)🎯 Exécutable $(NAME) créé$(RESET)\n"

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(OBJ_DIR):
	@printf " $(YELLOW)📁 Création des dossiers objets$(RESET)\n"
	@mkdir -p $(OBJ_DIR)/env
	@mkdir -p $(OBJ_DIR)/exec
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/signals
	@mkdir -p $(OBJ_DIR)/main
	@mkdir -p $(OBJ_DIR)/builtins

	@printf " $(BLUE)⚙️  Compilation des fichiers$(RESET)\n"
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(READLINE_FLAGS) -c $< -o $@

clean:
	@printf " $(YELLOW)🧹 Nettoyage des fichiers objets$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@printf " $(GREEN)✨ Nettoyage terminé$(RESET)"
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@printf " $(RED)🗑️  Suppression de l'exécutable minishell et de l'archive libft.a$(RESET)\n"
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@printf " $(GREEN)🧽 Nettoyage complet terminé$(RESET)\n"

re: fclean all
	@printf " $(BLUE)🔄 Recompilation terminée$(RESET)\n"

.PHONY: all clean fclean re
