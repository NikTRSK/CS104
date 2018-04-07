CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin

all: $(BIN_DIR)/lab5

$(BIN_DIR)/lab5: $(BIN_DIR)/.dirstamp $(BIN_DIR)/order.o
	$(CXX) $(CPPFLAGS) main.cpp $(BIN_DIR)/order.o -o $(BIN_DIR)/lab5

$(BIN_DIR)/order.o: $(BIN_DIR)/.dirstamp src/order.cpp lib/order.h
	$(CXX) $(CPPFLAGS) -c src/order.cpp -o $(BIN_DIR)/order.o

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp