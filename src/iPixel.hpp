#pragma once
#include <cstdint>
#include <array>
class iPixel {

public:
	iPixel(void);
	iPixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t global = 0x1f);
	void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t global = 0x1f);
	iPixel& operator=(iPixel& t);
	bool operator==(const iPixel& b) const;
	using Leds = std::array<iPixel, 10+87 + 82 + 2 + 5 * 14>;

	uint8_t Red(void);
	uint8_t Blue(void);
	uint8_t Green(void);

	static iPixel Interpolate(iPixel& A, iPixel& B, float f);

private:
	const uint8_t start : 3;
	uint8_t global : 5;
	uint8_t blue;
	uint8_t green;
	uint8_t red;
};



	

