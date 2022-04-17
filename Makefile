##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CPPFLAGS	=	-Wall -Wextra -Wno-Wsign-compare 

LDFLAGS = -lm -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC		= Liseuse.cpp 

OBJ		=	$(SRC:.cpp=.o)

NAME		=	liseuse



all: $(NAME)

clean:
	rm -f $(OBJ)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ) $(LDFLAGS)
		@echo -e "\e[92;5m       ====BULDING DONE====      \e[0m"

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
