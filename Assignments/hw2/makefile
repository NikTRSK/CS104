BIN_DIR = bin

CXX = g++
CPPFLAGS = -Wall -g

all: $(BIN_DIR)/hw2 $(BIN_DIR)/test

merge: $(BIN_DIR)/merge

llisttest: $(BIN_DIR)/test

$(BIN_DIR)/test: $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/llistint.o llisttest.cpp -o llisttest

$(BIN_DIR)/hw2: $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/llistint.o testAddToEmptyList.cpp -o testAddToEmptyList

$(BIN_DIR)/llistint.o: llistint.h llistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o $(BIN_DIR)/llistint.o

$(BIN_DIR)/merge:
	$(CXX) $(CPPFLAGS) hw2p6_merge.cpp -o hw2p6_merge

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) main

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp