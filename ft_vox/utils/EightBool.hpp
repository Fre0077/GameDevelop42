#pragma once

# include "../headers/inclusion.h"

class EightBool {
private:
	uint8_t	boolStore;
public:
	EightBool();
	~EightBool();

	void	SetBool(uint8_t n);

	uint8_t	GetBool(uint8_t n);
	uint8_t	GetValue();

	//class Overflow : public std::exception {
	//public:
	//	const char* what() const noexcept override {
	//		return "EightBool: give index higher than 7";
	//	}
	//};
};
