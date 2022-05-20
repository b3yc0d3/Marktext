CXX=g++
CXXFLAGS= -std=c++17 -Wall -Wextra -pedantic
LIBFLAGS=

SRC_DIR		= source
INCL_DIR	= includes
LIB_DIR		= libs
OUT_DIR		= build

SRC_FILES	= $(wildcard $(SRC_DIR)/*.cpp)

marktext:
	mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -o $(OUT_DIR)/mtt $(SRC_FILES)

debug:
	mkdir -p $(OUT_DIR)
	$(CXX) -g $(CXXFLAGS) $(LIBFLAGS) -o $(OUT_DIR)/mtt $(SRC_FILES)

valgrind:
	valgrind --leak-check=yes $(OUT_DIR)/mtt