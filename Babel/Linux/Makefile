CC	=	g++
RM	=	rm -f

SRC_SERV	=	babel_test_server_stash.cpp	\
				LinuxSocket.cpp			\
				../MutexVault.cpp		\
				../ISocket.cpp			\
				../Packet.cpp			\
				../Rsa.cpp				\
				../BBException.cpp		\
				../BabelServer.cpp		\
				../Sound/SoundManager.cpp	\
				../Sound/EncodeManager.cpp

SRC_CLIENT	=	babel_test_client_stash.cpp	\
				LinuxSocket.cpp			\
				../MutexVault.cpp		\
				../ISocket.cpp			\
				../Packet.cpp			\
				../Rsa.cpp				\
				../BBException.cpp		\
				../BabelClient.cpp		\
				../Sound/SoundManager.cpp	\
				../Sound/EncodeManager.cpp

OBJ_SERV	=	$(SRC_SERV:.cpp=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.cpp=.o)

NAME_S		=	server

NAME_C		=	client

LIBS		=	-L. -lpthread -lcrypto -lssl -L../Sound -lopus -lrt -lasound -ljack -lm -lportaudio -W -Wall -Wextra

all	:	$(NAME_S) $(NAME_C)

$(NAME_S):	$(OBJ_SERV)
		$(CC) $(OBJ_SERV) $(LIBS) -o $(NAME_S)

$(NAME_C):	$(OBJ_CLIENT)
		$(CC) $(OBJ_CLIENT) $(LIBS) -o $(NAME_C)

clean	:
		$(RM) $(OBJ_SERV) $(OBJ_CLIENT)

fclean	:	clean
		$(RM) $(NAME_S) $(NAME_C)

re	:	fclean all
