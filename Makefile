CFLAGS = -g -Wall
CXX = g++
SRC=./src
INC=./inc
OBJ=./obj

# Doxygen configuration
DOC_DIR = ./docs
DOXYFILE = Doxyfile

# Default target
all: prepare_dirs part1

# Prepare directories
prepare_dirs:
	@mkdir -p $(OBJ)

# Team target
team:
	@echo "Team Information:"
	@echo "CS601 Assignment 2"
	@echo "Team Member: Nilesh.R.Barandwal"

# Part I target: compile and link object files
part1: FEMain.o FEGrid.o Element.o Node.o
	$(CXX) $(OBJ)/FEMain.o $(OBJ)/FEGrid.o $(OBJ)/Element.o $(OBJ)/Node.o -o pa5

# Part II target: compile and link RDomain and Domain
#part2: RDomain.o FEMain.o
#	$(CXX) $(OBJ)/RDomain.o $(OBJ)/FEMain.o -o part2_executable

# Solution.o target: compile Solution.cpp
Solution.o: $(SRC)/Solution.cpp $(INC)/Solution.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Solution.o $(SRC)/Solution.cpp

# Part II target: compile and link RDomain, FEMain, FEGrid, Node, and Element
part2: RDomain.o FEMain.o FEGrid.o Node.o Element.o GridFn.o Solution.o
	$(CXX) $(OBJ)/RDomain.o $(OBJ)/FEMain.o $(OBJ)/FEGrid.o $(OBJ)/Node.o $(OBJ)/Element.o $(OBJ)/GridFn.o $(OBJ)/Solution.o -o part2_executable

GridFn.o: $(SRC)/GridFn.cpp $(INC)/GridFn.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/GridFn.o $(SRC)/GridFn.cpp

# FEMain.o target: compile FEMain.cpp
FEMain.o: $(SRC)/FEMain.cpp $(INC)/FEGrid.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/FEMain.o $(SRC)/FEMain.cpp

# Node.o target: compile Node.cpp
Node.o: $(SRC)/Node.cpp $(INC)/Node.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Node.o $(SRC)/Node.cpp

# Element.o target: compile Element.cpp
Element.o: $(INC)/Element.h $(SRC)/Element.cpp
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/Element.o $(SRC)/Element.cpp

# FEGrid.o target: compile FEGrid.cpp
FEGrid.o: $(INC)/FEGrid.h $(SRC)/FEGrid.cpp $(INC)/Element.h $(INC)/Node.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/FEGrid.o $(SRC)/FEGrid.cpp

# RDomain.o target: compile RDomain.cpp
RDomain.o: $(SRC)/RDomain.cpp $(INC)/RDomain.h $(INC)/Domain.h
	$(CXX) -I$(INC) $(CFLAGS) -c -o $(OBJ)/RDomain.o $(SRC)/RDomain.cpp

# Clean target: remove object files and executable, as well as Doxygen output
clean:
	rm -f $(OBJ)/* pa5 part1 part2_executable
	rm -rf $(DOC_DIR) ./html ./latex  # Remove Doxygen output

# Documentation target: generate Doxygen documentation
doc: $(DOXYFILE)
	@echo "Updating Doxyfile with input directories..."
	@mkdir -p $(DOC_DIR)            # Create docs directory if it doesn't exist
	sed -i 's|^INPUT =.*|INPUT = $(SRC) $(INC)|' $(DOXYFILE)
	@echo "INPUT = $(SRC) $(INC)" >> $(DOXYFILE)   # Append input directories to Doxyfile
	@echo "Appending project information to Doxyfile..."
	@echo "PROJECT_NAME = \"CS601: Software Development for Scientific Computing - CS24MT018\"" >> $(DOXYFILE)
	@echo "PROJECT_BRIEF = \"Programming Assignment 2 - Software for Computation on Grids\"" >> $(DOXYFILE)
	@echo "OUTPUT_DIRECTORY = ./docs" >> $(DOXYFILE)
	@echo "PROJECT_DESCRIPTION = \"This is an individual assignment. The objective of this assignment is to familiarize with grid codes and develop a generalized software solution for computing on grids.\"" >> $(DOXYFILE)
	@echo "PROJECT_VERSION = \"1.0\"" >> $(DOXYFILE)
	@echo "Generating Doxygen documentation..."
	doxygen $(DOXYFILE)

# Ensure the Doxyfile exists or create it
Doxyfile:
	echo "Doxyfile not found. Generating Doxyfile..."
	@doxygen -g
	@echo "Doxyfile generated. Please configure it if needed."

# Rebuild everything (including documentation)
rebuild: clean all doc

# Run Part II executable (after building)
runme: part2_executable
	@echo "Running Part II with the provided parameters..."
	./runme $(PARAMS)
