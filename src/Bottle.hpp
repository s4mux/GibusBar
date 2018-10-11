#pragma once

#include "iPixel.hpp"
#include <chrono>
#include <functional>

class Bottle {
public:
	Bottle(iPixel::Leds& leds, size_t index, size_t length = 14);
	void Process(void);
	void SetColor(iPixel& nextColor, std::chrono::milliseconds transitionTime = std::chrono::milliseconds { 0 }, std::function<void(Bottle&)> finish = nullptr);
private:
	iPixel::Leds& leds;
	const size_t index;
	const size_t length;

	iPixel actualColor;
	iPixel nexColor;

	std::chrono::system_clock::time_point startOfTransition;
	std::chrono::milliseconds transitionTime;

	std::function<void(Bottle&)> finish=nullptr;
};