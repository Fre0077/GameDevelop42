CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

LIBS = -lglfw -lGL -lGLEW -lm

SOURCES = ./src/main.cpp ./src/utils.cpp ./class/mat4.cpp
TARGET = scop

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(LIBS)

clean:
	@echo "No object files to clean"

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
