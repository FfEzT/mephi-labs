#pragma once

#include <string>
#include <unordered_map>
#include <functional>

#include "SFML/Graphics/Color.hpp"

#include "coord/Coords.h"

namespace config {
    using namespace GameLogic;


    constexpr bool DEBUG_FPS = false;
    constexpr bool DEBUG_ACTIVE_ID = true;

    const std::string MAP_PATH_FILE = "materials/map.txt";

    enum class ObjectType {
        LET = 1, INTEREST, COMMAND_CENTER, COMMAND_ROBOT, CENTER, SCOUT
    };

    constexpr unsigned FPS = 30;

    constexpr unsigned WINDOW_WIDTH = 1280;
    constexpr unsigned WINDOW_HEIGHT = 9 * WINDOW_WIDTH / 16;
    const std::string WINDOW_NAME = ("Babah Lol Ahmed");

    constexpr unsigned HEADER_HEIGHT = 32;

    constexpr unsigned FOOTER_HEIGHT = 128;
    constexpr unsigned FOOTER_SIZE_ONE_BLOCK = FOOTER_HEIGHT / 2;

    const sf::Color INTERFACE_COLOR = sf::Color(197, 197, 197);

    constexpr unsigned SIZE_ONE_BLOCK = 10;
    constexpr double SIZE_TEXTURE_BLOCK_PX = 64; // размер в пикселях текстуры объекта

    constexpr unsigned FIX = 1;

    constexpr unsigned COUNT_X_POSITION = 128;
    constexpr unsigned COUNT_Y_POSITION = 56;
}