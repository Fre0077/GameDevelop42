#include "EightBool.hpp"

EightBool::EightBool() {
	boolStore = 255;
}

EightBool::~EightBool() {}

void	EightBool::SetBool(uint8_t n) {
	//if(n > 7) throw Overflow();
	boolStore ^= (1 << n);
}

uint8_t	EightBool::GetBool(uint8_t n) {
	//if(n > 7) throw Overflow();
	return (boolStore >> n) & 1;
}

uint8_t	EightBool::GetValue() {
	return boolStore;
}