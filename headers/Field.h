#pragma once

#include <SFML/Graphics.hpp>
#include "settings.h"
#include <vector>

class Field {
private:
    class Cell {
    private:

        bool isOccupied = false;

    public:
        sf::RectangleShape cell;
        void setOccupied(const bool& Occupied) { isOccupied = Occupied; }
        bool getOccupied() const { return isOccupied; }

        sf::Vector2f getCenter() const {
            return sf::Vector2f(cell.getPosition().x + cell.getSize().x / 2, cell.getPosition().y + cell.getSize().y / 2);
        }
        void draw(sf::RenderWindow& window) { window.draw(cell); }
    };

    std::vector<std::vector<Cell>> field;

    float cellSize;
    float indent = 5;

public:
    Field(sf::RenderWindow& window, Settings& settings);

    void resize(sf::RenderWindow& window, Settings& settings);

    float getCellSize() const;
    Cell getCell(const sf::Vector2u& cellPos);

    void draw(sf::RenderWindow& window, Settings& settings);
};
