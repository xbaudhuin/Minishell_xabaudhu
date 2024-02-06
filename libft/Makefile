NAME			=	libft.a

SRC_PATH		=	src/

OBJ_PATH		=	obj/

CFLAGS			=	-Wall -Werror -Wextra
ifeq ($(DEBUG), 0)
	CFLAGS = -Wall -Werror -Wextra
endif

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
	CFLAGS += -fsanitize=address
endif

HEADER			=	-I ./include

SRCS			=	is_bool/ft_isalnum.c \
					is_bool/ft_isalpha.c \
					is_bool/ft_isascii.c \
					is_bool/ft_isdigit.c \
					is_bool/ft_isprint.c \
					is_bool/ft_tolower.c \
					is_bool/ft_toupper.c \
					mem/ft_bzero.c \
					mem/ft_calloc.c \
					mem/ft_memchr.c \
					mem/ft_memcmp.c \
					mem/ft_memcpy.c \
					mem/ft_memmove.c \
					mem/ft_memset.c \
					str/ft_atoi.c \
					str/ft_itoa.c \
					str/ft_split.c \
					str/ft_strchr.c \
					str/ft_strdup.c \
					str/ft_striteri.c \
					str/ft_strjoin.c \
					str/ft_strlcat.c \
					str/ft_strlcpy.c \
					str/ft_strlen.c \
					str/ft_strmapi.c \
					str/ft_strncmp.c \
					str/ft_strnstr.c \
					str/ft_strrchr.c \
					str/ft_strtrim.c \
					str/ft_substr.c \
					str/ft_join_split.c \
					put/ft_putchar_fd.c \
					put/ft_putendl_fd.c \
					put/ft_putnbr_fd.c \
					put/ft_putstr_fd.c \
					gnl/get_next_line.c \
					gnl/get_next_line_utils.c \
					list/ft_lstadd_back.c \
					list/ft_lstadd_front.c \
					list/ft_lstclear.c \
					list/ft_lstdelone.c \
					list/ft_lstiter.c \
					list/ft_lstlast.c \
					list/ft_lstmap.c \
					list/ft_lstnew.c \
					list/ft_lstsize.c \
					printf/ft_printf.c \
					printf/parse_flags.c \
					printf/print_char.c \
					printf/print_hexa.c \
					printf/print_memory.c \
					printf/print_signed.c \
					printf/print_string.c \
					printf/print_unsigned.c \
					printf/printf_utils.c \
					fprintf/ft_fprintf.c

RM				=	rm -rf

CC				=	cc

AR				=	ar rcs

OBJS			=	$(addprefix ${OBJ_PATH}, ${SRCS:.c=.o})

${NAME}:		${OBJS}
			@${AR} ${CLFAGS} ${NAME} ${OBJS}

${OBJ_PATH}%.o:	${SRC_PATH}%.c
			@mkdir -p $(dir $@)
			@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

all:		${NAME}

clean:
			@${RM} ${OBJ_PATH}

fclean:			clean
			@${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
