CXX 		= g++
CXXFLAGS	= -std=c++17 -Wall -Wextra -pedantic
LIBFLAGS	=
EXEC_FILE	= mt
EXEC_SUF	=
RM			= rm -r
SRC_DIR		= source
BUILD_DIR   = build

ifeq ($(detected_OS),Linux)
    CXX			= g++
else ifeq ($(detected_OS),FreeBSD)
	CXX 		= g++11
else ifeq ($(detected_OS),NetBSD)
	CXX 		= g++11
else ifeq ($(detected_OS),OpenBSD)
	CXX 		= g++11
else ifeq ($(detected_OS),DragonFly)
	CXX 		= g++11
else ifeq ($(detected_OS),Windows)
	EXEC_SUF	= .exe
	CXX 		= "C:\MinGW\bin\g++.exe"
endif

rwildcard 	= $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC_FILES 	= $(call rwildcard,$(SRC_DIR),*.cpp)
OBJ_FILES	= $(SRC_FILES:.cpp=.o)

.PHONY: clean install test

all: $(EXEC_FILE)

$(BUILD_DIR)/%.o: $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(EXEC_FILE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ -o $(BUILD_DIR)/$@

install:
	@echo "Work in progress"

clean:
	$(RM) $(OBJ_FILES)

test:
	@echo $(CXX)