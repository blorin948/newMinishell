$(VERBOSE).SILENT:

NAME =	minishell

LIBFT =	./libft/libft.a

PRINTF = ./ft_printf/libftprintf.a

FLAGS = gcc -Wall -Werror -Wextra

HEADERS = minishell.h

SRC =	check_split_lines.c\
		create.c\
		create_envir_export.c\
		create_fd.c\
		create_path.c\
		create_tab_redir.c\
		echo.c\
		exec.c\
		exit_free.c\
		export.c\
		export2.c\
		find_builtin.c\
		fonctions_annexe.c\
		get_next_line.c\
		init.c\
		lst_create.c\
		main.c\
		parse_dollars.c\
		parse_line.c\
		pwd_exit.c\
		remove_pipe_virgul.c\
		split_rest.c\
		start_parse_replace.c\
		unset.c\
		parse_antislash.c

OBJ = $(patsubst %.c, obj/%.o, $(SRC))

all: $(NAME)

$(OBJ): ${HEADERS}

$(NAME): $(OBJ) libf printf
	@echo "\n==> Making Minishell\n" 
	@$(FLAGS) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME)

libf:
	@echo "\n==> Making LIBFT"
	@make -C ./libft bonus

printf:
	@echo "\n==> Making PRINTF"
	@make -C ./ft_printf

obj/%.o: %.c
	@mkdir -p obj
	@$(FLAGS) -c $< -o $@

norme:
	norminette *.c *.h

clean:
	@echo "cleaning..."
	@rm -rf obj
	@make -C ./libft clean
	@echo done

fclean: clean
	@rm -rf $(NAME) obj
	@make -C ./libft fclean
	@make -C ./ft_printf fclean

re: fclean all

.PHONY:		all clean fclean re bonus run norme
