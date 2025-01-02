#include "headers/Field.h"

Field::Field(sf::RenderWindow& window, Settings& settings){ resize(window, settings); }

void Field::resize(sf::RenderWindow& window, Settings& settings) {
    field.resize(settings.field.size.x, std::vector<Cell>(settings.field.size.y));

    cellSize = window.getSize().y / settings.field.size.y - (indent / settings.field.size.y);

    for (unsigned int i = 0; i < settings.field.size.x; ++i) {
        for (unsigned int j = 0; j < settings.field.size.y; ++j) {

            field[i][j].cell.setSize(sf::Vector2f(cellSize - indent, cellSize - indent));
            field[i][j].cell.setFillColor(settings.field.cellColor);

            field[i][j].cell.setPosition(
                static_cast<float>(i * (cellSize) + indent),
                static_cast<float>(j * (cellSize) + indent)
            );
        }
    }
}

float Field::getCellSize() const{ return cellSize; }

Field::Cell Field::getCell(const sf::Vector2u& cellPos)
{
    return field[cellPos.x][cellPos.y];
}

void Field::draw(sf::RenderWindow& window, Settings& settings) {
    for (unsigned int i = 0; i < settings.field.size.x; ++i) {
        for (unsigned int j = 0; j < settings.field.size.y; ++j) {
            field[i][j].draw(window);
        }
    }
}
