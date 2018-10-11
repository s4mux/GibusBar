#include "Control.hpp"



Control::Control(void) :
	demo(leds),
	ambiente(leds)
 {
	mode = MODE::AMBIENTE;
 }

void Control::Update(void)
{
	switch (mode) {
	case MODE::WHITE:
		for (auto& led : leds) {
			led.setColor(255, 255, 255, 31);
		}
		break;
	case MODE::DEMO:
		demo.Update();
		break;
	case MODE::AMBIENTE:
		ambiente.Update();
		break;
	}
}


void Control::PushButton(void)
{
	switch (mode) {
	case MODE::WHITE:
		mode = MODE::DEMO;
		break;
	case MODE::DEMO:
		mode = MODE::AMBIENTE;
		break;
	case MODE::AMBIENTE:
		mode = MODE::WHITE;
		break;
	}
}


iPixel::Leds& Control::GetLeds(void)
{
	return leds;
}