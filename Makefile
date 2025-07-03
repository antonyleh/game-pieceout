CPP = g++ --std=c++11 -Wall
SFML_PATH = /opt/homebrew/opt/sfml
INCLUDE = -I$(SFML_PATH)/include
LIBS = -L$(SFML_PATH)/lib -lsfml-system -lsfml-graphics -lsfml-window

SRC = ebaucheVue.cpp \
      Controller/GameController.cpp \
      Model/GameModel.cpp \
      Model/Piece.cpp \
      Model/PieceConcrete.cpp \
      Model/PieceOperateur.cpp \
      Model/OperateurDeplacement.cpp \
      Model/OperateurRotation.cpp \
      Model/OperateurSymetrie.cpp

OBJ = $(SRC:.cpp=.o)
TARGET = pieceOut

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CPP) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.cpp
	$(CPP) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
