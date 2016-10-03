
INC = -I../NMath/Include

SRC = ../NMath/Source.cpp ../NMath/Source/graph/edge_data.cpp

OBJ = $(patsubst ../NMath/%.cpp,objects/%.o,$(SRC))

all: $(OBJ)
	echo $(OBJ)
	g++ -g -std=c++0x $(INC) $(OBJ) main.cpp

objects/%.o:../NMath/%.cpp
	mkdir -p $(dir $@)
	g++ -c -g -std=c++0x $(INC) $^ -o $@

