NAME = ft_vox
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++23

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

STB_HEADER = headers/stb_image.h
STB_URL = https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

all: $(STB_HEADER) $(NAME)

$(STB_HEADER):
	@echo "File $(STB_HEADER) non trovato. Scaricando..."
	wget -q $(STB_URL) -O $(STB_HEADER)
	@echo "Download completato"

$(NAME): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SOURCES) $(LIBS)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean $(NAME)

val: $(NAME)
	valgrind --suppressions=suppressions.supp  --error-limit=no --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./$(TARGET) $(ARGS)

.PHONY: clean fclean re val

