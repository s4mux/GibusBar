#pragma once

#include <vector>
#include <deque>
#include "iPixel.hpp"


class Demo {
public:
	Demo(iPixel::Leds& leds);
	void Update(void);
private:
	iPixel::Leds& leds;
	std::vector<iPixel> colors;

	size_t oldColor;
	std::deque<size_t> movings;
	size_t color;
	size_t fill;
};