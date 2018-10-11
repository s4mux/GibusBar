#pragma once

#include <vector>

#include "iPixel.hpp"


class Demo {
public:
	Demo(iPixel::Leds& leds);
	void Update(void);
private:
	iPixel::Leds& leds;
	std::vector<iPixel> colors;

	size_t oldColor;
	size_t moving;
	size_t color;
	size_t fill;

};