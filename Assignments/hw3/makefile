BIN_DIR = bin
CXX = g++
CPPFLAGS = -Wall -g
VALGRIND = valgrind --tool=memcheck --leak-check=yes
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

$(BIN_DIR)/llisttest: llistTest.cpp $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) $^ $(GTEST_LL) -o llisttest

$(BIN_DIR)/stacktest: stackTest.cpp $(BIN_DIR)/llistint.o $(BIN_DIR)/stackint.o
	$(CXX) $(CPPFLAGS) $^ -o stackTest

$(BIN_DIR)/parser: hw3p5_arith.cpp $(BIN_DIR)/stackint.o $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) $^ -o parser

llisttest: $(BIN_DIR)/llisttest

stack: $(BIN_DIR)/stacktest

parser: $(BIN_DIR)/parser

$(BIN_DIR)/llistint.o: llistint.h llistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o $(BIN_DIR)/llistint.o

$(BIN_DIR)/stackint.o: stackint.h stackint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c stackint.cpp -o $(BIN_DIR)/stackint.o

.PHONY: run_llisttest
run_llisttest: $(BIN_DIR)/llisttest
	-./llisttest
	-@echo "--- All Tested!---"
grind_llisttest: $(BIN_DIR)/llisttest
	-$(VALGRIND) ./llisttest
	-@echo "--- All Tested!---"

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) main

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp