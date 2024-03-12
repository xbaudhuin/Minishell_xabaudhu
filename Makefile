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

SRCS_WILDCARD	=	wildcard/opendir.c \
					wildcard/wildcard.c \
					wildcard/wildcard_expansion.c \
					wildcard/wildcard_split.c \
					wildcard/wildcard_utils.c \
					wildcard/trim_quotes_wildcard.c \
					wildcard/get_nb_wildcard.c \

SRCS_HERE_DOC	=	here_doc/here_doc.c \
					here_doc/here_doc_dup.c \
					here_doc/here_doc_stdin.c \

SRCS_EXPAND		=	expand/expand.c \
					expand/expand_dollar.c \
					expand/re_tokenize.c \
					expand/trim_quotes_all.c \
					expand/copy_dollar.c \
					expand/copy_dollar_utils.c \
					expand/len_dollar.c \
					expand/len_dollar_utils.c \

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

SRCS_EXEC		=	exec/launch_tree.c \
					exec/launch_node.c \
					exec/pipeline/launch_pipeline.c \
					exec/pipeline/set_pipe_redirection.c \
					exec/pipeline/open_pipe.c \
					exec/command/set_cmd_redirection.c \
					exec/command/launch_cmd.c \
					exec/command/execute_a_cmd.c \
					exec/builtin/launch_builtin.c \
					exec/builtin/set_builtin_redirection.c \
					exec/files/is_stdin.c \
					exec/files/is_stdout.c \
					exec/files/open_cmd_files.c \
					exec/files/close_cmd_files.c \
					exec/fork/get_last_child_status.c \
					exec/fork/end_process.c \
					exec/exec_cmd_struct/free_data.c \
					exec/exec_cmd_struct/free_exec_cmd.c \
					exec/exec_cmd_struct/get_cmd_argv.c \
					exec/exec_cmd_struct/initialize_exec_cmd.c \
					exec/exec_cmd_struct/get_cmd_path.c \
					exec/exec_cmd_struct/construct_path.c \

SRCS_SIGNALS	=	signals/quit_signal.c \
					signals/int_signal.c \

SRCS_MAIN		=	main.c \
					minishell.c \

OBJS			=	$(addprefix ${OBJ_PATH}, ${SRCS_EXEC:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_PARSING:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_WILDCARD:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_HERE_DOC:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_EXPAND:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_ENVIRONMENT:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_BUILTINS:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_SIGNALS:.c=.o}) \
					$(addprefix ${OBJ_PATH}, ${SRCS_MAIN:.c=.o}) \

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


