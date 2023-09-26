SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_printf.c \
		ft_putadd.c \
		ft_putchar.c \
		ft_putnbr_hex.c \
		ft_putnbr_ptr.c \
		ft_putnbr.c \
		ft_putnbru.c \
		ft_putstr.c \
		ft_strncpy.c \
		get_next_line.c \

OBJS = $(addprefix ./objs/, $(SRCS:.c=.o))

INCLUDES = libft.h

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

RM = rm -rf

AR = ar rcs

./objs/%.o:	./srcs/%.c $(INCLUDES)
			@mkdir -p objs
			$(CC) $(CFLAGS) -c $< -o $@ -I.

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean:
			$(RM) objs

all:		$(NAME)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re