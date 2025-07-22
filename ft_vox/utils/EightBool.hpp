#ifndef EIGHTBOOL_HPP
# define EIGHTBOOL_HPP

# include "../headers/inlcusion.h"

class EightBool {
private:
	char	boolStore;
public:
	EightBool();
	~EightBool();

	void	SetBool(uint8_t n);

	uint8_t	GetBool(uint8_t n);

	//class Overflow : public std::exception {
	//public:
	//	const char* what() const noexcept override {
	//		return "EightBool: give index higher than 7";
	//	}
	//};
};

#endif