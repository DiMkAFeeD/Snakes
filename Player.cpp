#include "headers/Player.h"

sf::Vector2f Lerp(const sf::Vector2f& startPoint, const sf::Vector2f& endPoint, float elapsedTime, float totalTime) {
	if (elapsedTime >= totalTime) {
		return endPoint;
	}
	float t = elapsedTime / totalTime;
	return startPoint + t * (endPoint - startPoint);
}

Player::Player(Settings& settings, Field& field) {
	head.setFillColor(settings.player.color);
	position = sf::Vector2u(
		(settings.field.size.x % 2 == 0) ? settings.field.size.x / 2 : (settings.field.size.x - 1) / 2,
		(settings.field.size.y % 2 == 0) ? settings.field.size.y / 2 : (settings.field.size.y - 1) / 2
	);
	field.getCell(position).setOccupied(true);
}

void Player::setHeadSize(const sf::Vector2f& newSize){ head.setSize(newSize);}
void Player::setTarget()
{

}

void Player::Move(Field& field)
{
	if (field.getCell(targetPos).getCenter() == headPosition) {
		clock.restart();
		dirOff = sf::Vector2f();
		position = targetPos;
		targetPos = sf::Vector2u();
	}
	dirOff = field.getCell(position).getCenter() - Lerp(field.getCell(lastPos).getCenter(), field.getCell(targetPos).getCenter(), clock.getElapsedTime().asSeconds(), 2);
}

void Player::Update(Field& field, const float& deltaTime, Settings& settings) {
	head.setSize(sf::Vector2f(field.getCellSize() / 4 * 3, field.getCellSize() / 4 * 3));
	head.setPosition(headPosition);
	head.move(dirOff);

		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction = Direction::up;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = Direction::left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction = Direction::down;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = Direction::right;


	switch (moveDir)
	{
    case Player::Direction::none:
		moveDir = direction;
   		break;
    case Player::Direction::up:
		targetPos = position + sf::Vector2u(0, 1);
		break;
    case Player::Direction::left:
		targetPos = position + sf::Vector2u(-1, 0);
		break;
    case Player::Direction::down:		
		targetPos = position + sf::Vector2u(0, -1);
		break;
    case Player::Direction::right:
		targetPos = position + sf::Vector2u(1, 0);
		break;
    default:
   		break;
	}
	Move(field);

}
	
void Player::draw(sf::RenderWindow& window)
{
	head.move(sf::Vector2f(-head.getSize().x / 2, -head.getSize().y / 2));
	window.draw(head);
}
