BIN_DIR = bin
SRC_DIR = src
CXX = g++
CPPFLAGS = -Wall -g
VALGRIND = valgrind --tool=memcheck --leak-check=yes
STATEMENT = src/Statement.h
TARGETS = $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o $(BIN_DIR)/ProgramState.o $(BIN_DIR)/LetStatement.o $(BIN_DIR)/EndStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/PrintAllStatement.o $(BIN_DIR)/AddStatement.o $(BIN_DIR)/SubStatement.o $(BIN_DIR)/MultStatement.o $(BIN_DIR)/DivStatement.o $(BIN_DIR)/GotoStatement.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/GoSubStatement.o $(BIN_DIR)/ReturnStatement.o
#GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(TARGETS)

facile: facile

# Compiles any .o file by using the .cpp and .h file of the same name. 
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp $(filter-out Statement.h, $(SRC_DIR)/%.h) $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

facile: $(SRC_DIR)/Facile.cpp $(TARGETS)
	$(CXX) $(CPPFLAGS) $^ -o $@

grind_facile: facile
	-$(VALGRIND) ./facile
	-@echo "--- All Tested!---"

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) main

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp