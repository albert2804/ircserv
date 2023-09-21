
SHELL 			=	/bin/bash
CPPFLAGS		= 	-Wall -Wextra -Werror -std=c++98 -g
CXX 			= 	c++
# ---------------------------------------#

NAME			=	ircserv


SRC				= 	main \
					Client.Class \
					Channel.Class \
					Server.Class \
					parsing \
					commands \
					numericReplies
					



SRC_FILES		=	$(addsuffix .c, $(SRC))
OBJ_FILES		=	$(addsuffix .o, $(SRC))

all: $(NAME)

%.o: %.c
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ_FILES)
	$(CXX) $(CPPFLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	@if find ${OBJ_FILES} > /dev/null 2>&1; then \
		rm -f $(OBJ_FILES); \
	fi

fclean: clean
	@rm -f ${NAME};

re: fclean all

.PHONY: all clean fclean re