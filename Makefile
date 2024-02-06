NAME			=	pipex

BONUS			=	pipex_bonus

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

CFLAGS			=	-Wall -Werror -Wextra

RM				=	rm -rf

AR				=	ar rcs

SRCS			=	mandatory/pipex.c \
					mandatory/ft_split_pipex.c \
					mandatory/error.c \
					mandatory/get_path.c \
					mandatory/child.c

SRCS_BONUS		=	bonus/error_bonus.c \
					bonus/ft_split_pipex_bonus.c \
					bonus/get_path_bonus.c \
					bonus/child_bonus.c \
					bonus/pipex_bonus.c \
					bonus/here_doc.c

OBJS			=	$(addprefix ${OBJ_PATH}, ${SRCS:.c=.o})

OBJS_BONUS		=	$(addprefix ${OBJ_PATH}, ${SRCS_BONUS:.c=.o})

LIBFT_D			=	$(addprefix ${LIBFT_PATH}, ${LIBFT})

all:			${NAME}

bonus:			${BONUS}

${NAME}:		${LIBFT} ${OBJS} ${TXT}
		@${CC} ${CFLAGS} -g -o ${NAME} ${OBJS} ${HEADER} ${LIBFT}
		@echo "${COLOUR_GREEN}${NAME} Compiled${COLOUR_END}"

${BONUS}:	${LIBFT} ${OBJS_BONUS} ${TXT}
		@${CC} ${CFLAGS} -g -o ${BONUS} ${OBJS_BONUS} ${HEADER} ${LIBFT}
		@echo "${COLOUR_GREEN}${BONUS} Compiled${COLOUR_END}"

${OBJ_PATH}%.o:	${SRC_PATH}%.c
		@mkdir -p $(dir $@)
		@${CC} -g ${CFLAGS} ${HEADER} -c $< -o $@

${LIBFT}:
		@make -C ${LIBFT_PATH} --no-print-directory
		@cp ${LIBFT_PATH}${LIBFT} .
		@echo "$(COLOUR_GREEN)Libft Compiled${COLOUR_END}"

${TXT}:
		@echo "-Ilibft/include\n-Iinclude/" > compile_flags.txt
		@echo "-I../../libft/include\n-Iinclude/" > src/bonus/compile_flags.txt
		@echo "-I../../libft/include\n-Iinclude/" > src/mandatory/compile_flags.txt

clean:
		make -C ${LIBFT_PATH} clean --no-print-directory
		${RM}  ${OBJ_PATH}

fclean:		clean
		make -C ${LIBFT_PATH} fclean --no-print-directory
		${RM} ${NAME} ${BONUS} ${LIBFT} ${SRC_PATH}mandatory/${TXT} ${SRC_PATH}bonus/${TXT} ${TXT}

re:			fclean all

.PHONY:		all fclean clean re libft


