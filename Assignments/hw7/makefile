#BIN_DIR = bin
#SRC_DIR = src
CXX = g++
CPPFLAGS = -Wall -g
VALGRIND = valgrind --tool=memcheck --leak-check=yes
STATEMENT = src/Statement.h
#GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

#all: $(TARGETS)

exam_scheduling: exam_scheduling

exam_scheduling: exam_scheduling.cpp bst.h avlbst.h scheduling.h
	$(CXX) $(CPPFLAGS) $^ -o $@

grind_facile: exam_scheduling
	-$(VALGRIND) ./exam_scheduling
	-@echo "--- All Tested!---"

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) main

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp