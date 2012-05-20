##
## Makefile for  in /home/xaqq/Documents/network
##
## Made by arnaud kapp
## Login   <kapp_a@epitech.net>
##
## Started on  Tue Feb 14 18:18:42 2012 arnaud kapp
## Last update Sun May 20 04:20:55 2012 arnaud kapp
##

NAME=		libmynet.so

SRC=		src/ATcpClient.cpp \
		src/TcpServer.cpp \
		src/TcpSocket.cpp \
		src/RingBuffer.cpp

OBJ=		$(SRC:.cpp=.o)

CXXFLAGS+=	-O3 -W -Wall -I ./includes -fPIC

$(NAME):	$(OBJ)
		g++ -fPIC -o $(NAME) $(OBJ) -shared

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean $(NAME)
