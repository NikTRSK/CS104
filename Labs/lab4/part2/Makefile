# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_DIR)/arrayTest: test.cpp $(BIN_DIR)/arraylist.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

.PHONY: tests

tests: $(BIN_DIR)/arrayTest
	-@$(BIN_DIR)/arrayTest
	-@echo "--- All Tested!---"
