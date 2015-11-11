CC	=	g++

RM	=	rm -f

SRC	=	EncodeManager.cpp	\
		SoundManager.cpp	\
		main.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	Test

LIBS	=	-L. -lopus -lrt -lasound -ljack -lpthread -lm -lportaudio

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) $(LIBS) -o $(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
