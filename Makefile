# Compiler and flags
CFLAGS = -g -Wall
CXX = g++
SRC = ./src
INC = ./inc
OBJ = ./obj
EXE = pa5

# Doxygen configuration
DOC_DIR = ./docs
DOXYFILE = Doxyfile

# All target
all: part1

# Build the executable
part1: FEMain.o FEGrid.o Element.o Node.o
	$(CXX) $(OBJ)/FEMain.o $(OBJ)/FEGrid.o $(OBJ)/Element.o $(OBJ)/Node.o -o $(EXE)

# Compile FEMain.o
FEMain.o: $(SRC)/FEMain.cpp $(INC)/FEGrid.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/FEMain.o $(SRC)/FEMain.cpp

# Compile Node.o
Node.o: $(SRC)/Node.cpp $(INC)/Node.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Node.o $(SRC)/Node.cpp

# Compile Element.o
Element.o: $(INC)/Element.h $(SRC)/Element.cpp
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Element.o $(SRC)/Element.cpp

# Compile FEGrid.o
FEGrid.o: $(INC)/FEGrid.h $(SRC)/FEGrid.cpp $(INC)/Element.h $(INC)/Node.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/FEGrid.o $(SRC)/FEGrid.cpp

# Update the Doxyfile with the correct input paths and run Doxygen
docs: $(DOXYFILE)
	@echo "Updating Doxyfile with input directories..."
	sed -i 's|^INPUT =.*|INPUT = $(SRC) $(INC)|' $(DOXYFILE)
	doxygen $(DOXYFILE)

# Clean up generated files
clean:
	rm -f ./obj/*.o $(EXE)          # Remove object files and executable
	rm -rf ./docs/*                  # Remove Doxygen output

# Rebuild everything (including documentation)
rebuild: clean all docs
