#
##		VARS
#

RM		=	rm -rf
COLOR_OFF	=	\033[0m
COLOR_ON	=	\033[34;01m

SERVER_PROG	=	$(COLOR_ON) [/_\ Server Compiled /_\] $(COLOR_OFF)
CLIENT_PROG	=	$(COLOR_ON) [/_\ Client Compiled /_\] $(COLOR_OFF)
GRAPHIC_PROG	=	$(COLOR_ON) [/_\ Graphic Compiled /_\] $(COLOR_OFF)

CLIENT_NAME 	=	zappy_ai
SERVER_NAME	=	zappy_server
GRAPHIC_NAME	=	zappy_gui

S_SRC		=	./Server/Sources/add_client.c			\
			./Server/Sources/broadcast_graphic.c		\
			./Server/Sources/broadcasts.c			\
			./Server/Sources/calcul_coord_broadcast.c	\
			./Server/Sources/check_incantation.c		\
			./Server/Sources/connect_client.c		\
			./Server/Sources/connect_nbr.c			\
			./Server/Sources/cycle.c			\
			./Server/Sources/direction_broadcast.c		\
			./Server/Sources/erase_client.c			\
			./Server/Sources/expulse.c			\
			./Server/Sources/forkp.c			\
			./Server/Sources/graphic_cycle.c		\
			./Server/Sources/graphic_handle.c		\
			./Server/Sources/graphic_handle2.c		\
			./Server/Sources/graphic_handle3.c		\
			./Server/Sources/graphic_response.c		\
			./Server/Sources/graphic_response2.c		\
			./Server/Sources/graphic_response3.c		\
			./Server/Sources/graphic_response4.c		\
			./Server/Sources/graphic_response5.c		\
			./Server/Sources/handle_client.c		\
			./Server/Sources/handle_graphic.c		\
			./Server/Sources/handle_options.c		\
			./Server/Sources/handle_options_fct.c		\
			./Server/Sources/handle_signals.c		\
			./Server/Sources/handle_waiting_player.c	\
			./Server/Sources/incantation.c			\
			./Server/Sources/incantation2.c			\
			./Server/Sources/init.c				\
			./Server/Sources/inventaire.c			\
			./Server/Sources/main.c				\
			./Server/Sources/manage_player.c		\
			./Server/Sources/manage_ressource.c		\
			./Server/Sources/player_cmd.c			\
			./Server/Sources/player_cmd2.c			\
			./Server/Sources/scan_voir.c			\
			./Server/Sources/send_data.c			\
			./Server/Sources/start_server.c			\
			./Server/Sources/tab_diagonal_broadcast.c	\
			./Server/Sources/tab_direction_broadcast.c	\
			./Server/Sources/voir.c				\
			./Server/Sources/voir_element.c			\
			./Server/Sources/list.c				\
			./Server/Sources/list_1.c			\
			./Server/Sources/str_to_wordtab.c		\
			./Server/Sources/functions.c

C_SRC		=	./Client/Sources/Correspondances.cpp		\
			./Client/Sources/Lexer.cpp			\
			./Client/Sources/main.cpp			\
			./Client/Sources/Network.cpp			\
			./Client/Sources/ZappyIa.cpp

G_SRC		=	./Graphic/Sources/main.cpp			\
			./Graphic/Sources/AssetsManager.cpp		\
			./Graphic/Sources/Commands.cpp			\
			./Graphic/Sources/Event.cpp			\
			./Graphic/Sources/Line.cpp			\
			./Graphic/Sources/CondVar.cpp			\
			./Graphic/Sources/GetLine.cpp			\
			./Graphic/Sources/Mutex.cpp			\
			./Graphic/Sources/GameEngine.cpp		\
			./Graphic/Sources/Network.cpp			\
			./Graphic/Sources/Requests.cpp			\
			./Graphic/Sources/Routine.cpp			\
			./Graphic/Sources/ScopedLock.cpp

S_OBJ		=	$(S_SRC:.c=.o)
C_OBJ		=	$(C_SRC:.cpp=.o)
G_OBJ		=	$(G_SRC:.cpp=.o)

#
##		RULES
#

all		:	$(SERVER_NAME) $(CLIENT_NAME) $(GRAPHIC_NAME)


$(SERVER_NAME)	:	CFLAGS = -W -Wall -Wextra -Werror -I./Server/Includes

$(CLIENT_NAME)	:	CXXFLAGS = -W -Wall -Wextra -Werror -std=c++11 -I./Client/Includes
$(CLIENT_NAME)	:	LDLIBS = -lpthread

$(GRAPHIC_NAME)	:	CXXFLAGS = -W -Wall -Wextra -Werror \
				   -I./Graphic/Includes -I./Graphic/SFML/include
$(GRAPHIC_NAME)	:	LDLIBS = -lpthread  -L./Graphic/SFML/lib -Wl,-rpath=./Graphic/SFML/lib \
				 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

$(SERVER_NAME)	:	$(S_OBJ)
			gcc -o $(SERVER_NAME) $(S_OBJ)
			@echo -e "$(SERVER_PROG)"

$(CLIENT_NAME)	:	$(C_OBJ)
			g++ -o $(CLIENT_NAME) $(C_OBJ) $(LDLIBS)
			@echo -e "$(CLIENT_PROG)"

$(GRAPHIC_NAME)	:	$(G_OBJ)
			g++ -o $(GRAPHIC_NAME) $(G_OBJ) $(LDLIBS)
			@echo -e "$(GRAPHIC_PROG)"

clean		:
			$(RM) $(S_OBJ)
			$(RM) $(C_OBJ)
			$(RM) $(G_OBJ)

fclean		:	clean
			$(RM) $(SERVER_NAME)
			$(RM) $(CLIENT_NAME)
			$(RM) $(GRAPHIC_NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
