
NAME =	minishell

LIBFT =	./libft/libft.a

PRINTF = ./ft_printf/libftprintf.a

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
		split_rest.c\
		create_fd.c\
		parse_line.c\
		check_split_lines.c\
		start_parse_replace.c\
		export2.c

OBJ = $(patsubst %.c, obj/%.o, $(SRC))

all: $(NAME)

$(OBJ): ${HEADERS}

$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	@echo "\n==> Making Minishell"
	$(FLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)

$(LIBFT):
	@echo "\n==> Making LIBFT"
	make -C ./libft bonus

$(PRINTF):
	@echo "\n==> Making printf"
	make -C ./ft_printf

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
