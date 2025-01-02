#include <SFML/Graphics.hpp>

#include "headers/Field.h"
#include "headers/Player.h"

int main() {
	Settings settings;

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), L"Змейка", sf::Style::Fullscreen);

	float deltaTime = 0;
	sf::Clock clock;

	Field field(window, settings);
	Player player(settings, field);

	sf::View view;
	view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed: {
				window.close(); 
			}
			case sf::Event::Resized: {
				view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
				field.resize(window, settings);
				player.setHeadSize(sf::Vector2f(field.getCellSize(), field.getCellSize()));
			}
			default:
				break;
			}
		}

		deltaTime = clock.restart().asSeconds();

		player.Update(field, deltaTime, settings);

		window.clear(settings.bg.color);
		window.setView(view);

		field.draw(window, settings);
		player.draw(window);

		window.display();
	}
}