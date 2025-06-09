# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = 

SRCS = main.cpp row_negative_counter.cpp matrix_diagonal_sum.cpp battleship_counter.cpp

TARGET = program.out

BUILD_DIR = build

OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.cpp subtasks.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
