#include "../headers/inclusion.h"

//FUNZIONE ESCLUSIVA: utilizzata per testare il perlin noise in worldgenerator
void printVec(const std::vector<float> &vec) {
	if (vec.size() != 256) {
		std::cerr << "Vector must contain exactly 256 elements (16x16).\n";
		return;
	}

	const char* levels = " .:-=+*#%@";

	for (int i = 0; i < 256; i++) {
		float val = vec[i];
		val = val / 2.0f;
		int level = static_cast<int>(val * 9);
		std::cout << levels[level] << " ";
		if ((i + 1) % 16 == 0)
			std::cout << std::endl;
	}
}

//stampa un vector di float
void	printVecF(const std::vector<float> &vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
}

//FUNZIONE ESCLUSIVA: utilizzata nel rendering
void	pushVertex(Vertex &ver, std::vector<float> &vec) {
	vec.push_back(ver.x);
	vec.push_back(ver.y);
	vec.push_back(ver.z);
	vec.push_back(ver.u);
	vec.push_back(ver.v);
}

//calcola l'index nel vector corrispondente alle cooridnate date
int	index(int &x, int &y, int &z) {
	return (y * 16 * 16) + (z * 16) + x;
}

//cicla tutti i blocchi di un chunck
bool cicle(int &x, int &y, int &z) {
	y++;
	if (y >= 256) {
		y = 0;
		x++;
		if (x >= 16) {
			x = 0;
			z++;
			if (z >= 16)
				return false;
		}
	}
	return true;
}

//restituisce il resto di a % b
float	rest(float a, int b) {
	while (a > b)
		a -= b;
	return a;
}

//valore assoluto
float	Abs(float a) {
	if (a > 0)
		return a;
	return a * -1;
}

//aumenta il valore a di augment, se è negativo aumenta negativamente e viceversa
void	augment(int &a, int augment) {
	if (a > 0)
		a += augment;
	else
		a -= augment;
}