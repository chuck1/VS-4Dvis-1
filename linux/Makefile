
<<<<<<< HEAD
INC = -I../../NMath/Include

SRC = ../../NMath/Source.cpp

all:
	g++ -std=c++0x $(INC) $(SRC) main.cpp
=======
INC = -I../NMath/Include

SRC = ../NMath/Source.cpp ../NMath/Source/graph/edge_data.cpp

OBJ = $(patsubst ../NMath/%.cpp,objects/%.o,$(SRC))

all: $(OBJ)
	echo $(OBJ)
	g++ -g -std=c++0x $(INC) $(OBJ) main.cpp

objects/%.o:../NMath/%.cpp
	mkdir -p $(dir $@)
	g++ -c -g -std=c++0x $(INC) $^ -o $@
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7

