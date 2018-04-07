#BIN_DIR = bin
#SRC_DIR = src
CXX = g++
CPPFLAGS = -Wall -g -std=c++11
VALGRIND = valgrind --tool=memcheck --leak-check=yes
STATEMENT = src/Statement.h
#GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

zipf: zipf

zipf: zipf.cpp bst.h Map.h splayTree.h splayTree.cpp hashMap.h hashMap.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) main

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp