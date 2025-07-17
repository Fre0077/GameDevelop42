CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

LIBS = -lglfw -lGL -lGLEW -lm

SOURCES = ./src/main.cpp ./src/utils.cpp ./class/mat4.cpp ./class/rendering.cpp
TARGET = scop

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

fclean: clean

re: fclean $(TARGET)

val: $(TARGET)
	valgrind --suppressions=suppressions.supp  --error-limit=no --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./$(TARGET) $(ARGS)

.PHONY: clean fclean re val

