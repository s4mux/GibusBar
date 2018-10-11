#include <SFML/Graphics.hpp>

#include "Control.hpp"

#include <array>
#include <iostream>
#include <cstdlib>

sf::Color pixelToColor(iPixel& pixel) {
	sf::Color color(pixel.Red(), pixel.Green(), pixel.Blue());
	return color;
}




int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Gibus BAR");
		
	Control ledControl;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Event::MouseButtonPressed == event.type) {
				if (sf::Mouse::Button::Left == event.mouseButton.button) {
					std::cout << "Mouse LEFT" << std::endl;
					ledControl.PushButton();
				}
				else if (sf::Mouse::Button::Right == event.mouseButton.button) {
					std::cout << "Mouse RIGHT" << std::endl;
					ledControl.PushButton();
				}
			}
		}


		window.clear();

		ledControl.Update();

		auto leds = ledControl.GetLeds();
		size_t ledIndex = 0;


		for (size_t i = 0; i < 10; i++) {
			sf::CircleShape pixel(2.f);
			pixel.setPosition(5 * 90, 85 * 5 -i*4.6);
			pixel.setFillColor(pixelToColor(leds.at(ledIndex++)));
			window.draw(pixel);
		}

		for (size_t i = 0; i < 87; i++) {
			sf::CircleShape pixel(2.f);
			pixel.setPosition(5*90-4 - i*4.6, 65*5);
			pixel.setFillColor(pixelToColor(leds.at(ledIndex++)));
			window.draw(pixel);
		}

		for (size_t i = 0; i < 82; i++) {
			sf::CircleShape pixel(2.f);
			pixel.setPosition(70 + i*4.6, 30 * 5);
			pixel.setFillColor(pixelToColor(leds.at(ledIndex++)));
			window.draw(pixel);
		}

		ledIndex++;
		ledIndex++;
		


		for (size_t i = 0; i < 5; i++) {

			for (size_t k = 0; k < 7; k++) {
				sf::RectangleShape segment(sf::Vector2f(4 * 5, 15 * 5/7));
				segment.setPosition((76 - i * 14) * 5, 25 * 5-(k+1)*(15 * 5 / 7));
				segment.setFillColor(pixelToColor(leds.at(ledIndex++)));
				window.draw(segment);
			}

			for (size_t p = 0; p < 7; p++) {
				sf::CircleShape pixel(2.f);
				pixel.setPosition((76 - i * 14) * 5-7, 3+25 * 5 - (p + 1)*(15 * 5 / 7));
				pixel.setFillColor(pixelToColor(leds.at(ledIndex++)));
				window.draw(pixel);
			}


		}

		window.display();
		sf::sleep(sf::milliseconds(40));
	}

	return 0;
}