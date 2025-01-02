#include "headers/settings.h"

Settings::Settings() {
    if (isInitialized) return;

    std::ifstream settingsFile("settings.json");
    if (!settingsFile.is_open()) {
        std::cerr << "Error: Could not open settings.json" << std::endl;
        return;
    }

    settingsFile >> settings;

    if (settings.contains("bg") && settings["bg"].contains("color")) {
        parseJsonToColor(settings["bg"]["color"], bg.color);
    }

    if (settings.contains("field")) {
        if (settings["field"].contains("size")) {
            field.size.x = settings["field"]["size"].value("x", 0);
            field.size.y = settings["field"]["size"].value("y", 0);
        }
        if (settings["field"].contains("cellColor")) {
            parseJsonToColor(settings["field"]["cellColor"], field.cellColor);
        }
    }

    if (settings.contains("player") && settings["player"].contains("color")) {
        parseJsonToColor(settings["player"]["color"], player.color);
    }

    isInitialized = true;
}

void Settings::parseJsonToColor(const json& colorJson, sf::Color& color) {
    if (colorJson.is_object()) {
        color.r = colorJson.value("red", 0);
        color.g = colorJson.value("green", 0);
        color.b = colorJson.value("blue", 0);
        color.a = colorJson.value("alpha", 255);
    }
}
