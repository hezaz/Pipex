#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := pipex
CC        := gcc
FLAGS    := -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      bonus/src/pipex_bonus.c \
                          mandatory/src/pipex.c \
                          libft/ft_strnstr.c \
                          libft/ft_isdigit.c \
                          libft/ft_lstadd_back.c \
                          libft/ft_putstr_fd.c \
                          libft/ft_lstnew.c \
                          libft/get_next_line_utils.c \
                          libft/ft_strlcpy.c \
                          libft/ft_strlen.c \
                          libft/ft_printf_utils.c \
                          libft/ft_lstlast.c \
                          libft/ft_memcmp.c \
                          libft/ft_putnbr.c \
                          libft/ft_putnbr_fd.c \
                          libft/ft_lstclear.c \
                          libft/ft_lstiter.c \
                          libft/ft_strnlen.c \
                          libft/ft_strchr.c \
                          libft/ft_printf.c \
                          libft/ft_striteri.c \
                          libft/ft_bzero.c \
                          libft/ft_strjoin.c \
                          libft/ft_isascii.c \
                          libft/ft_memcpy.c \
                          libft/ft_strstr.c \
                          libft/get_next_line.c \
                          libft/ft_memccpy.c \
                          libft/ft_isprint.c \
                          libft/ft_putendl_fd.c \
                          libft/ft_free.c \
                          libft/ft_lstmap.c \
                          libft/ft_lstsize.c \
                          libft/ft_toupper.c \
                          libft/ft_split.c \
                          libft/ft_lstadd_front.c \
                          libft/ft_putchar.c \
                          libft/ft_strrchr.c \
                          libft/ft_isalpha.c \
                          libft/ft_memchr.c \
                          libft/ft_putchar_fd.c \
                          libft/ft_memset.c \
                          libft/ft_substr.c \
                          libft/ft_strncmp.c \
                          libft/ft_strmapi.c \
                          libft/ft_strtrim.c \
                          libft/ft_memmove.c \
                          libft/ft_putstr.c \
                          libft/ft_strlcat.c \
                          libft/ft_calloc.c \
                          libft/ft_strdup.c \
                          libft/ft_atoi.c \
                          libft/ft_isalnum.c \
                          libft/ft_lstdelone.c \
                          libft/ft_itoa.c \
                          libft/ft_tolower.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} -o ${NAME} ${OBJS}
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re


