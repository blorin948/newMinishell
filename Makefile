
NAME =	minishell

LIBFT =	./libft/libft.a

FLAGS = gcc

HEADERS = minishell.h

SRC =	main.c\
		get_next_line.c\
		create.c\
		init.c\
		exec.c\
		create_path.c\
		find_builtin.c\
		fonctions_annexe.c\
		echo.c\
		export.c\
		unset.c\
		pwd_exit.c\
		create_envir_export.c\
		lst_create.c\
		exit_free.c\
		remove_pipe_virgul.c\
		parse_dollars.c\
		create_tab_redir.c\
		split_rest.c

OBJ = $(patsubst %.c, obj/%.o, $(SRC))

all: $(NAME)

$(OBJ): ${HEADERS}

$(NAME): $(LIBFT) $(OBJ)
	@echo "\n==> Making Minishell"
	$(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@echo "\n==> Making LIBFT"
	make -C ./libft bonus

obj/%.o: %.c
	mkdir -p obj
	$(FLAGS) -c $< -o $@

norme:
	norminette *.c *.h

run: $(NAME)
	./minishell

clean:
	rm -rf obj
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME) obj
	make -C ./libft fclean

re: fclean all
