#pragma once

#include "iPixel.hpp"
#include "Bottle.hpp"

void BottleFinish(Bottle& bottle);

class Ambiente {
public:
	Ambiente(iPixel::Leds& leds);
	void Update(void);

private:
	iPixel::Leds& leds;
	Bottle bottleA;
	Bottle bottleB;
	Bottle bottleC;
	Bottle bottleD;
	Bottle bottleE;
	Bottle borTop;
	Bottle barBot;
	Bottle barCtrl;
};
