NAME = philo

SRCS =	philo.c \
		libft.c \
		inits.c \
		routine_break.c \
		routine_f.c \
		time.c 

OBJECT = $(SRC:.c=.o)


all : $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror $(SRCS) -o $(NAME) -pthread -g #-fsanitize=address
	@echo "\033[32mPhilosophers Compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
	@rm -f $(OBJECT)
	@echo "🗑️ 🗑️ 🗑️"
fclean: clean
	@rm -f $(NAME)
	@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"
re: fclean all

.PHONY: all clean fclean re
