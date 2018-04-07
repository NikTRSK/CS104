# In this Makefile we'll introduce the concepts of Makefile automatic variables
# Make will simply substitute these variables with the corresponding string
# $< - first dependency
# $^ - all dependencies
# $@ - target name (whatever's before colon)

# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread
TARGETS = $(BIN_DIR)/player.o $(BIN_DIR)/healer.o $(BIN_DIR)/tank.o $(BIN_DIR)/fighter.o $(BIN_DIR)/inventory.o

all: $(TARGETS)
	-@echo "--- All Built!---"

# Compiles any .o file by using the .cpp and .h file of the same name. 
$(BIN_DIR)/%.o: %.cpp %.h $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

# $^ is an auto variable that means "all dependencies"
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_DIR)/RPGTest: test.cpp $(TARGETS)
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

# Rule to ensure the $(BIN_DIR) directory exist or it'll create it.
# $@ is an auto variable that means "target name", which is $(BIN_DIR)/.dirstamp in this case
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $@

.PHONY: clean tests

tests: clean $(BIN_DIR)/RPGTest
	-@$(BIN_DIR)/RPGTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
