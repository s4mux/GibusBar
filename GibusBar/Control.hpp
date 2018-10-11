#pragma once

#include "iPixel.hpp"
#include "Demo.hpp"
#include "Ambiente.hpp"

std::chrono::milliseconds GetMsTime(void);

class Control {
public:
	enum class MODE{
		DEMO,
		AMBIENTE,
		WHITE
	};
	Control(void);
	void Update(void);
	void PushButton(void);

	iPixel::Leds& GetLeds(void);

private:
	iPixel::Leds leds;
	MODE mode;
	Demo demo;
	Ambiente ambiente;
};
