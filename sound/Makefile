CC	=	g++

RM	=	rm -f

SRC	=	SoundManager.cpp	\
		EncodeManager.cpp	\
		main.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	Test

LIBS	=	-lportaudio -lopus

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
