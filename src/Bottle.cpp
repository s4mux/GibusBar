#include "Bottle.hpp"

#include <chrono>

Bottle::Bottle(iPixel::Leds& leds, size_t index, size_t length) :
	leds(leds),
	index(index),
	length(length)
{

}

void Bottle::Process(void)
{
	if (nexColor == actualColor) {
		for (size_t i = index; i < index + length; i++) {
			leds.at(i) = actualColor;
		}
	}
	else{
		auto t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startOfTransition);
		float f = (float)t.count() / (float)transitionTime.count();
		for (size_t i = index; i < index + length; i++) {
			leds.at(i) = iPixel::Interpolate(actualColor, nexColor, f);
		}
		if (f > 1.0) {
			actualColor = nexColor;
			if (finish) {
				finish(*this);
			}
		}
	}
}

void Bottle::SetColor(iPixel& nextColor, std::chrono::milliseconds transitionTime, std::function<void(Bottle&)> finish)
{
	startOfTransition = std::chrono::system_clock::now();
	this->transitionTime = transitionTime;
	this->nexColor = nextColor;
	this->finish = finish;

	if (std::chrono::milliseconds{ 0 } == transitionTime) {
		actualColor = nexColor;
		if (finish) {
			finish(*this);
		}
	}
}