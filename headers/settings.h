#pragma once

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>


using json = nlohmann::json;

class Settings {
private:
    bool isInitialized = false;

    struct Background {
        sf::Color color;
    };
    struct Player {
        sf::Color color;
    };
    struct Field {
        sf::Vector2u size;
        sf::Color cellColor;
    };

    void parseJsonToColor(const json& colorJson, sf::Color& color);

public:
    Background bg;
    Player player;
    Field field;

    json settings;

    Settings();
};
