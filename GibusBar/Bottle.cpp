#include "Bottle.hpp"

#include <chrono>

#include <sstream>

std::chrono::milliseconds GetMsTime(void);
void ArduinoDebug(std::ostringstream& oss);

Bottle::Bottle(iPixel::Leds& leds, size_t index, size_t length) :
	leds(leds),
	index(index),
	length(length)
{

}

void Bottle::Process(void)
{
  
   std::ostringstream debug;
	if (nexColor == actualColor) {
		for (size_t i = index; i < index + length; i++) {
			leds.at(i) = actualColor;
		}
	}
	else{
		auto t = (GetMsTime() - startOfTransition);
		float f = (float)t.count() / (float)transitionTime.count();
   debug << "time is" << t.count() << "and f: " << f;
    iPixel interpolatedColor = iPixel::Interpolate(actualColor, nexColor, f);
		for (size_t i = index; i < index + length; i++) {
			leds.at(i) = interpolatedColor;
		}
		if (f > 1.0) {
			actualColor = nexColor;
			if (finish) {
				finish(*this);
			}
		}
	}
 
   //ArduinoDebug(debug);
}

void Bottle::SetColor(iPixel& nextColor, std::chrono::milliseconds transitionTime, std::function<void(Bottle&)> finish)
{
  #if 0
	startOfTransition = std::chrono::system_clock::now();
 #else
startOfTransition = GetMsTime();
 #endif
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
