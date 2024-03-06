NAME			=	minishell

BONUS			=	minishell_bonus

CFLAGS			=	-Wall -Werror -Wextra

DEBUG 			= 	0

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

HEADER_FILES	=	include/minishell.h \
					include/builtins.h \
					include/environment.h \
					include/exec.h \
					include/expand.h \
					include/my_signals.h \
					include/parsing.h \
					include/structures.h \
					libft/include/ft_printf.h \
					libft/include/get_next_line.h \
					libft/include/libft.h \


COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

SRC_PATH		=	src/

OBJ_PATH		=	obj/

CC				=	cc

RM				=	rm -rf

AR				=	ar rcs

SRCS_PARSING	=	parsing/check_special_char2.c \
					parsing/check_special_char.c \
					parsing/token_add_back.c \
					parsing/is_token.c \
					parsing/previous_token.c \
					parsing/previous_token2.c \
					parsing/parse_to_token.c \
					parsing/parse_to_token_utils.c \
					parsing/check_token_list.c \
					parsing/transform_token.c \
					parsing/simplify_token_list.c \
					parsing/dup_word.c \
					parsing/t_command.c \
					parsing/create_node.c \
					parsing/create_tree.c \
					parsing/tree_utils.c \
					parsing/free_function.c \
					debug.c \
					parsing/read_line.c \

SRCS_WILDCARD	=	wildcard/opendir.c \
					wildcard/wildcard.c \
					wildcard/wildcard_split.c \
					wildcard/wildcard_utils.c \
					wildcard/trim_quotes_wildcard.c \

SRCS_HERE_DOC	=	here_doc/here_doc.c \
					here_doc/here_doc_dup.c \
					here_doc/here_doc_stdin.c \

SRCS_EXPAND		=	expand/expand.c \
					expand/expand_dollar.c \
					expand/re_tokenize.c \
					expand/trim_quotes_all.c \
					expand/copy_dollar.c \
					expand/len_dollar.c \

SRCS_ENVIRONMENT =	environment/free_env.c \
					environment/create_env.c \
					environment/ft_getenv.c \
					environment/get_expanded_env.c \
					environment/add_pwd.c \
					environment/add_shlvl.c \
					environment/update_shlvl.c \
					environment/get_first_null_address.c \
					environment/get_last_var_address.c \

SRCS_BUILTINS 	=	builtins/echo/echo.c \
					builtins/env/env.c \
					builtins/export/export.c \
					builtins/pwd/pwd.c \
					builtins/builtin_utils.c \
					builtins/unset/unset.c \
					builtins/cd/cd.c \
					builtins/exit/exit.c \
					builtins/is_builtin.c \
					builtins/check_option.c \
					builtins/is_var_name_valid.c \
					builtins/exit/atoll_check_of.c \

SRCS_EXEC		=	exec/open_cmd_files.c \
					exec/get_cmd_path.c \
					exec/get_cmd_argv.c \
					exec/launch_cmd.c \
					exec/end_process.c \
					exec/launch_tree.c \
					exec/launch_node.c \
					exec/launch_pipeline.c \
					exec/launch_builtin.c \
					exec/initialize_exec_cmd.c \
					exec/free_exec_cmd.c \
					exec/free_data.c \
					exec/set_builtin_redirection.c \
					exec/get_last_child_status.c \
					exec/open_pipe.c \
					exec/close_cmd_files.c \
					exec/set_pipe_redirection.c \
					exec/set_cmd_redirection.c \
					exec/execute_a_cmd.c \
					exec/is_stdin.c \
					exec/is_stdout.c \

SRCS_TEST		=	test_builtins.c \
					signals/quit_signal.c \
					signals/int_signal.c \

OBJS			=	$(addprefix ${OBJ_PATH}, ${SRCS_EXEC:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_PARSING:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_WILDCARD:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_HERE_DOC:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_EXPAND:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_ENVIRONMENT:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_BUILTINS:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_TEST:.c=.o}) \

LIBFT_D			=	$(addprefix ${LIBFT_PATH}, ${LIBFT})

################################################################################
#                                 RULES                                        #
################################################################################
					
all:			${NAME}

bonus:			${BONUS}

${NAME}:		${LIBFT} ${OBJS} ${TXT} ${HEADER_FILES}
		@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${HEADER} ${LIBFT} -lreadline
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
		@echo "-I../libft/include\n-I../include/" > src/compile_flags.txt

clean:
		make -C ${LIBFT_PATH} clean --no-print-directory
		${RM}  ${OBJ_PATH}

fclean:		clean
		make -C ${LIBFT_PATH} fclean --no-print-directory
		${RM} ${NAME} ${NAME_TEST} ${BONUS} ${LIBFT} ${SRC_PATH}/${TXT} ${SRC_PATH}bonus/${TXT} ${TXT}

re:			fclean all

.PHONY:		all fclean clean re libft


