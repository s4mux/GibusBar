#include "Ambiente.hpp"

#if 0
void BottleFinish(Bottle& bottle) {
  
	uint8_t r = rand() % 256;
	uint8_t g = rand() % 256;
	uint8_t b = rand() % 256;
	size_t time = rand() % 30000 + 5000;

  iPixel clr(r, g, b);
  bottle.SetColor(clr, std::chrono::milliseconds{ time }, BottleFinish);
}
#endif

Ambiente::Ambiente(iPixel::Leds& leds) : 
	leds(leds),
 bottleA(leds, 237),
 bottleB(leds, 223),
 bottleC(leds, 209),
 bottleD(leds, 195),
 bottleE(leds, 181),
 borTop(leds, 97, 82),
 barBot(leds, 10, 87),
	barCtrl(leds, 0, 10)
 {
	iPixel startColor(0, 0, 0);

	bottleA.SetColor(startColor);
	bottleB.SetColor(startColor);
	bottleC.SetColor(startColor);
	bottleD.SetColor(startColor);
	bottleE.SetColor(startColor);
	borTop.SetColor(startColor);
	barBot.SetColor(startColor);
	barCtrl.SetColor(startColor);

	startColor.setColor(200, 200, 200);

	bottleA.SetColor(startColor, std::chrono::seconds(100), BottleFinish);
	bottleB.SetColor(startColor, std::chrono::seconds(100), BottleFinish);
	bottleC.SetColor(startColor, std::chrono::seconds(100), BottleFinish);
	bottleD.SetColor(startColor, std::chrono::seconds(100), BottleFinish);
	bottleE.SetColor(startColor, std::chrono::seconds(100), BottleFinish);
	borTop.SetColor(startColor, std::chrono::seconds(100), BottleFinish);
	barBot.SetColor(startColor, std::chrono::seconds(100), BottleFinish);
	barCtrl.SetColor(startColor, std::chrono::seconds(100), BottleFinish);
 }

void Ambiente::Update(void)
{
	bottleA.Process();
	bottleB.Process();
	bottleC.Process();
	bottleD.Process();
	bottleE.Process();
	borTop.Process();
	barBot.Process();
	barCtrl.Process();
}
