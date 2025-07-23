NAME = ft_vox
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

LIBS = -lglfw -lGL -lGLEW -lm

SOURCES =	./WorldGenerator.cpp \
			./VertexCreator.cpp \
			./DataManager.cpp \
			./Rendering.cpp \
			./Texture.cpp \
			./main.cpp \
			./utils/EightBool.cpp \
			./utils/Vector.cpp \
			./utils/utils.cpp \
			./utils/Voxel.cpp

$(NAME): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SOURCES) $(LIBS)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean $(NAME)

val: $(NAME)
	valgrind --suppressions=suppressions.supp  --error-limit=no --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./$(TARGET) $(ARGS)

.PHONY: clean fclean re val

