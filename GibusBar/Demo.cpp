#include "Demo.hpp"

Demo::Demo(iPixel::Leds& leds) :
	leds(leds)
{
	colors.emplace_back(0, 0, 0);

	colors.emplace_back(200, 0, 0);
	colors.emplace_back(0, 200, 0);
	colors.emplace_back(0, 0, 200);
	colors.emplace_back(35, 250, 170);
	colors.emplace_back(0, 100, 200);
	colors.emplace_back(0, 250, 50);
	colors.emplace_back(0, 255, 100);
	colors.emplace_back(200, 200, 200);
 

	color = 1;
	oldColor = 0;
	movings.emplace_back(0);
	fill = 0;
}



void Demo::Update(void)
{
	for (auto& led : leds) {
		led = colors.at(oldColor);
	}

	for (auto& moving : movings) {
		leds.at(moving) = colors.at(color);
		moving++;
	}

	if (movings.size() && movings.back() > 6) {
		movings.push_back(0);
	}

	for (size_t i = leds.size() - fill; i < leds.size(); i++) {
		leds.at(i) = colors.at(color);
	}

	if (movings.size() &&  movings.front() + fill >= leds.size()) {
		movings.pop_front();
		fill++;

		if (0 == movings.size()) {
			movings.push_back(0);
		}

		if (fill >= leds.size()) {
			fill = 0;
			oldColor = color;
			color++;
			if (color >= colors.size()) {
				color = 0;
			}
			movings.clear();
			movings.push_back(0);
		}
	}
}
