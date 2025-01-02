#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include "Field.h"
#include <functional>

class Player {
private:
	sf::RectangleShape head;

	enum class Direction {
		none, up, left, down, right
	};

	bool isAchieved = true;

	sf::Clock clock;

	sf::Vector2f targetPos;
	Direction direction = Direction::none; // нажатое направление
	Direction moveDir; // направление куда едет

	sf::Vector2f headPosition; 
	sf::Vector2u position; // позиция в клетках
	
	sf::Vector2u lastPos;
	sf::Vector2u targetPos;
	sf::Vector2f dirOff;

	void Move(Field& field);
	void setTarget();
public:
	Player(Settings& settings, Field& field);

	void setHeadSize(const sf::Vector2f& newSize);

	void Update(Field& field, const float& deltaTime, Settings& settings);
	void draw(sf::RenderWindow& window);
};