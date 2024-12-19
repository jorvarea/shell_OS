NAME = a.out

CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Werror
RM = rm -f

SRC = $(wildcard src/*.c) $(wildcard *.c)
OBJ = $(SRC:src/%.c=obj/%.o)
DEPS = $(wildcard include/*.h) $(wildcard *.h)

################################################################################
##                                  COLORS                                    ##
################################################################################

END=\033[0m
BOLD=\033[1m
GREEN=\033[0;32m
RED=\033[0;31m
YELLOW=\033[33m

################################################################################
##                                  RULES                                     ##
################################################################################

all : line $(NAME)

$(NAME) : $(OBJ)
	@echo "$(GREEN)✦ ---------------------- ✦"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "  ✓  Linked: $(NAME)"
	@echo "✦ ---------------------- ✦$(END)"

obj/%.o : src/%.c | obj
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)  ✓ Compiled: $(notdir $<)$(END)"

obj:
	@mkdir -p obj

line :
	@echo "$(GREEN) $(BOLD)"
	@echo "  COMPILING SHELL...$(END) $(GREEN)"
	@echo "✦ ---------------------- ✦"

clean :
	@printf "\n$(YELLOW) 🗑   Removing objects$(END)\n"
	@$(RM) $(OBJ)
	@rmdir obj 2> /dev/null || true
	@echo "$(GREEN)  ✓  Removed objects $(END)"

fclean: clean
	@printf "$(YELLOW) 🗑   Removing $(NAME) $(END)\n"
	@$(RM) $(NAME)
	@echo "$(GREEN)  ✓  Removed $(NAME) $(END)\n"

re : fclean all

.PHONY: all clean fclean re