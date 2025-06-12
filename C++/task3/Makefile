CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRC = main.cpp
BIN = program.out

all: $(BIN)

$(BIN): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)

.PHONY: all clean
