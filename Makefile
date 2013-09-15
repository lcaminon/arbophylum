SRC=	main.cpp \
	Graph.cpp \
	Entity.cpp \
	Ressources.cpp

NAME=	arbre

OBJ =	$(SRC:.cpp=.o)

CXX =	g++ 

CXXFLAGS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
