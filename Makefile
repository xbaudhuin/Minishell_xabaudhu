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
	CFLAGS += -g -fsanitize=address
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

SRCS			=	mandatory/read_line.c\

SRCS_BONUS		=	\

OBJS			=	$(addprefix ${OBJ_PATH}, ${SRCS:.c=.o})

OBJS_BONUS		=	$(addprefix ${OBJ_PATH}, ${SRCS_BONUS:.c=.o})

LIBFT_D			=	$(addprefix ${LIBFT_PATH}, ${LIBFT})

all:			${NAME}

bonus:			${BONUS}

${NAME}:		${LIBFT} ${OBJS} ${TXT} include/minishell.h libft/include/ft_printf.h libft/include/get_next_line.h libft/include/libft.h
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
		@echo "-I../../libft/include\n-I../../include/" > src/bonus/compile_flags.txt
		@echo "-I../../libft/include\n-I../../include/" > src/mandatory/compile_flags.txt

clean:
		make -C ${LIBFT_PATH} clean --no-print-directory
		${RM}  ${OBJ_PATH}

fclean:		clean
		make -C ${LIBFT_PATH} fclean --no-print-directory
		${RM} ${NAME} ${BONUS} ${LIBFT} ${SRC_PATH}mandatory/${TXT} ${SRC_PATH}bonus/${TXT} ${TXT}

re:			fclean all

.PHONY:		all fclean clean re libft


