NAME = pipex

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

LIBFT = ./LIBFT

LIBFT_AR = ./libft/libft.a

SR_PATH = ./src/

OB_PATH = ./obj/

INCLUDE = -I ./header/pipex.h

SR =	\

SRCS = ${addprefix ${SR_PATH}, ${SR}}

OBJS = ${addprefix ${OB_PATH}, ${SR:.c=.o}}

all: ${NAME}

${OB_PATH}%.o : ${SR_PATH}%.c
			@mkdir -p ${OB_PATH}
			cc -c $< -o $@

${NAME}:	${OBJS}
			make -C ${LIBFT}
			cc -o ${NAME} ${INCLUDE} ${OBJS} ${LIBFT_AR}

clean:
			make clean -C ${LIBFT}
			${RM} ${OBJS}
			${RM} -r ${OB_PATH}
fclean: clean
			make fclean -C ${LIBFT}
			${RM} ${NAME}

re: fclean all

.PHONY: 