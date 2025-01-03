#include "headers/Player.h"
#include <iostream>

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

    setTarget(settings);
    std::cout << "[DEBUG] Player initialized at position: " << position.x << ", " << position.y << "\n";
}

void Player::setHeadSize(const sf::Vector2f& newSize) {
    head.setSize(newSize);
}

void Player::chekLose(Settings& settings) {
    if (targetPos.x >= settings.field.size.x || targetPos.y >= settings.field.size.y) {
        isLose = true;
        std::cout << "[DEBUG] Player lost! Target position out of bounds: " << targetPos.x << ", " << targetPos.y << "\n";
    }
}

void Player::setTarget(Settings& settings) {
    lastPos = position;
    switch (direction) {
    case Player::Direction::up:
        targetPos = position + sf::Vector2u(0, -1);
        break;
    case Player::Direction::down:
        targetPos = position + sf::Vector2u(0, 1);
        break;
    case Player::Direction::left:
        targetPos = position + sf::Vector2u(-1, 0);
        break;
    case Player::Direction::right:
        targetPos = position + sf::Vector2u(1, 0);
        break;
    case Player::Direction::none:
    default:
        targetPos = position;
        break;
    }
    chekLose(settings);
    if (!isLose) {
        std::cout << "[DEBUG] New target set: " << targetPos.x << ", " << targetPos.y << "\n";
    }
}

void Player::Move(Field& field, Settings& settings) {
    if (isLose) return;

    if (headPosition == field.getCell(targetPos).getCenter()) {
        position = targetPos;
        dirOff = sf::Vector2f(0, 0);
        setTarget(settings);
        clock.restart();
        std::cout << "[DEBUG] Reached position: " << position.x << ", " << position.y << "\n";
    }

    if (targetPos.x < settings.field.size.x && targetPos.y < settings.field.size.y) {
        sf::Vector2f newPos = Lerp(
            field.getCell(lastPos).getCenter(),
            field.getCell(targetPos).getCenter(),
            clock.getElapsedTime().asSeconds(),
            0.5f
        );
        dirOff = newPos - field.getCell(position).getCenter();
        std::cout << "[DEBUG] Moving to target: dirOff (" << dirOff.x << ", " << dirOff.y << ")\n";
    }
}

void Player::Update(Field& field, const float& deltaTime, Settings& settings) {
    if (!isLose) {
        head.setSize(sf::Vector2f(field.getCellSize() / 4 * 3, field.getCellSize() / 4 * 3));
        headPosition = field.getCell(position).getCenter() + dirOff;
        head.setPosition(headPosition);
        head.move(sf::Vector2f(-head.getSize().x / 2, -head.getSize().y / 2));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) direction = Direction::up;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) direction = Direction::left;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) direction = Direction::down;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) direction = Direction::right;

        Move(field, settings);
    }
    else {
        std::cout << "[DEBUG] Player cannot move, game over.\n";
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(head);
}
