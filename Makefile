SHELL 		:= /bin/sh

CXX 		= g++
CXXFLAGS	= -std=c++17 -Wall -Wextra -pedantic
LIBFLAGS	=
EXEC_NAME	= mt

SRC_DIR		= source
INCL_DIR	= includes
LIB_DIR		= libs
BUILD_DIR   = build
OBJECT_DIR	= objects

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC_FILES = $(call rwildcard,$(SRC_DIR),*.cpp)

marktext:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LIBFLAGS) -o $(BUILD_DIR)/$(EXEC_NAME) $(SRC_FILES)

debug:
	mkdir -p $(BUILD_DIR)
	$(CXX) -g $(CXXFLAGS) $(LIBFLAGS) -o $(BUILD_DIR)/$(EXEC_NAME) $(SRC_FILES)

valgrind:
	valgrind --leak-check=yes $(BUILD_DIR)/$(EXEC_NAME)