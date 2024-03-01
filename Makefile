NAME			=	minishell

BONUS			=	minishell_bonus

CFLAGS			=	-Wall -Werror -Wextra

DEBUG 			= 0

ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

ifeq ($(DEBUG), 2)
	CFLAGS += -g2
endif

ifeq ($(DEBUG), 3)
	CFLAGS += -g3
endif

ifeq ($(DEBUG), 4)
	CFLAGS += -g3 -fsanitize=address
endif

LIBFT			=	libft.a

TXT				=	compile_flags.txt

LIBFT_PATH		=	libft/

HEADER			=	-I./include -I./libft/include

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

SRC_PATH		=	src/

OBJ_PATH		=	obj/

CC				=	cc

RM				=	rm -rf

AR				=	ar rcs

SRCS_PARSING	=	mandatory/parsing/check_special_char2.c \
					mandatory/parsing/check_special_char.c \
					mandatory/parsing/token_add_back.c \
					mandatory/parsing/is_token.c \
					mandatory/parsing/previous_token.c \
					mandatory/parsing/previous_token2.c \
					mandatory/parsing/parse_to_token.c \
					mandatory/parsing/parse_to_token_utils.c \
					mandatory/parsing/check_token_list.c \
					mandatory/parsing/transform_token.c \
					mandatory/parsing/simplify_token_list.c \
					mandatory/parsing/dup_word.c \
					mandatory/parsing/t_command.c \
					mandatory/parsing/create_node.c \
					mandatory/parsing/create_tree.c \
					mandatory/parsing/tree_utils.c \
					mandatory/parsing/free_function.c \
					mandatory/debug.c \
					mandatory/parsing/read_line.c \

SRCS_WILDCARD	=	mandatory/wildcard/opendir.c \
					mandatory/wildcard/wildcard.c \
					mandatory/wildcard/wildcard_split.c \
					mandatory/wildcard/wildcard_utils.c \
					mandatory/wildcard/trim_quotes_wildcard.c \

SRCS_HERE_DOC	=	mandatory/here_doc/here_doc.c \
					mandatory/here_doc/here_doc_dup.c \
					mandatory/here_doc/here_doc_stdin.c \

OBJS			=	$(addprefix ${OBJ_PATH}, ${SRCS_PARSING:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_WILDCARD:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_HERE_DOC:.c=.o}) \


LIBFT_D			=	$(addprefix ${LIBFT_PATH}, ${LIBFT})

################################################################################
#                                 TEST_LEO                                     #
################################################################################

NAME_TEST		=	test.exe

SRCS_ENVIRONMENT =	mandatory/environment/free_env.c \
					mandatory/environment/create_env.c \
					mandatory/environment/ft_getenv.c \
					mandatory/environment/get_expanded_env.c \

SRCS_BUILTINS 	=	mandatory/builtins/echo/echo.c \
					mandatory/builtins/env/env.c \
					mandatory/builtins/export/export.c \
					mandatory/builtins/pwd/pwd.c \
					mandatory/builtins/builtin_utils.c \
					mandatory/builtins/unset/unset.c \
					mandatory/builtins/cd/cd.c \
					mandatory/builtins/exit/exit.c \
					mandatory/builtins/is_builtin.c \
					mandatory/builtins/check_option.c \
					mandatory/builtins/is_var_name_valid.c \

SRCS_EXEC		=	mandatory/exec/open_cmd_files.c \
					mandatory/exec/get_cmd_path.c \
					mandatory/exec/get_cmd_argv.c \
					mandatory/exec/launch_cmd.c \
					mandatory/exec/end_process.c \
					mandatory/exec/launch_tree.c \
					mandatory/exec/launch_node.c \
					mandatory/exec/launch_pipeline.c \
					mandatory/exec/launch_builtin.c \
					mandatory/exec/initialize_exec_cmd.c \
					mandatory/exec/free_exec_cmd.c \
					mandatory/exec/free_data.c \
					mandatory/exec/set_builtin_redirection.c \
					mandatory/exec/get_last_child_status.c \
					mandatory/exec/open_pipe.c \
					mandatory/exec/close_cmd_files.c \
					mandatory/exec/set_pipe_redirection.c \
					mandatory/exec/set_cmd_redirection.c \
					mandatory/exec/execute_a_cmd.c \

SRCS_TEST		=	mandatory/test_builtins.c \
					mandatory/signals/quit_signal.c \
					mandatory/signals/int_signal.c \

OBJS_EXEC		=	$(addprefix ${OBJ_PATH}, ${SRCS_EXEC:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_PARSING:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_WILDCARD:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_HERE_DOC:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_ENVIRONMENT:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_BUILTINS:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_TEST:.c=.o}) \

################################################################################
#                                 RULES                                        #
################################################################################
					
all:			${NAME}

bonus:			${BONUS}

${NAME}:		${LIBFT} ${OBJS} ${TXT} include/minishell.h libft/include/ft_printf.h libft/include/get_next_line.h libft/include/libft.h
		@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${HEADER} ${LIBFT} -lreadline
		@echo "${COLOUR_GREEN}${NAME} Compiled${COLOUR_END}"

test : 			${NAME_TEST}

${NAME_TEST}:	${LIBFT} ${OBJS_EXEC} ${TXT} include/minishell.h libft/include/ft_printf.h libft/include/get_next_line.h libft/include/libft.h
		@${CC} ${CFLAGS} -o ${NAME_TEST} ${OBJS_EXEC} ${HEADER} ${LIBFT} -lreadline
		@echo "${COLOUR_GREEN}${NAME} Compiled${COLOUR_END}"

${BONUS}:	${LIBFT} ${OBJS_BONUS} ${TXT}
		@${CC} ${CFLAGS} -o ${BONUS} ${OBJS_BONUS} ${HEADER} ${LIBFT}
		@echo "${COLOUR_GREEN}${BONUS} Compiled${COLOUR_END}"

${OBJ_PATH}%.o:	${SRC_PATH}%.c
		@mkdir -p $(dir $@)
		@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

${LIBFT}:
		@make -C ${LIBFT_PATH} DEBUG=$(DEBUG) --no-print-directory
		@cp ${LIBFT_PATH}${LIBFT} .
		@echo "$(COLOUR_GREEN)Libft Compiled${COLOUR_END}"

${TXT}:
		@echo "-Ilibft/include\n-Iinclude/" > compile_flags.txt
		@echo "-I../../libft/include\n-I../../include/" > src/mandatory/compile_flags.txt

clean:
		make -C ${LIBFT_PATH} clean --no-print-directory
		${RM}  ${OBJ_PATH} 

fclean:		clean
		make -C ${LIBFT_PATH} fclean --no-print-directory
		${RM} ${NAME} ${NAME_TEST} ${BONUS} ${LIBFT} ${SRC_PATH}mandatory/${TXT} ${SRC_PATH}bonus/${TXT} ${TXT}

re:			fclean all

.PHONY:		all fclean clean re libft


