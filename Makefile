##
## Makefile for  in /home/xaqq/Documents/network
##
## Made by arnaud kapp
## Login   <kapp_a@epitech.net>
##
## Started on  Tue Feb 14 18:18:42 2012 arnaud kapp
## Last update Wed Apr 18 19:36:45 2012 arnaud kapp
##

NAME=		libmynet.so

SRC=		src/tcpsrv.c \
		src/tcpsrv_create.c \
		src/tcpsrv_delete.c \
		src/tcpsrv_bind_listen.c \
		src/tcpsrv_run.c \
		src/tcpclient.c \
		src/ring_buffer/ring_buffer.c \
		src/ring_buffer/ring_buffer_st.c \
		src/flags.c \
		src/select_manager.c \
		src/write.c \
		src/ring_buffer/ring_buffer_read.c

OBJ=		$(SRC:.c=.o)

CFLAGS+=	-O3 -W -Wall -I ./includes -fPIC

$(NAME):	$(OBJ)
		gcc -fPIC -o $(NAME) $(OBJ) -shared

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean $(NAME)
