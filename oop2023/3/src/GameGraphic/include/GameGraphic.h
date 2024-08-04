#pragma once

#include <optional>
#include <memory>

#include "SFML/Graphics.hpp"

#include "config.h"
#include "enviroment/Enviroment.h"
#include "engine/AI.h"

namespace graphic {
    using namespace GameLogic;
    using namespace engine;

    using namespace config;

    using namespace sf;

    using std::unique_ptr;
    using std::unordered_map;

    // TODO GOD OBJECT
    class GameGraphic {
    public:
        GameGraphic();

        void cycle();

    private:
        using optionalMouse = std::optional<Vector2f>;
        using optional = std::optional<id_t>;

        Enviroment env = Enviroment(
            COUNT_X_POSITION, COUNT_Y_POSITION,
            unique_ptr<IEngine>(new AI)
        );

        RenderWindow window;

        Texture commandModuleTexture;
        Texture sensorTexture;
        Texture generatorTexture;
        Texture gridTexture;

        // TODO это должно задаваться в конструкторе по идее
        unordered_map<id_t, Texture> mapTextures;

        optional activePlatformId = std::nullopt;
        optional activePointInterestId = std::nullopt;

        IMoveable& getActiveMoveable();

        void loadMap();

        void loadTextures();

        void render(optionalMouse& mouseClick);

        void drawHeader();

        void drawFooter();

        void drawGrid();

        void drawObjects(optionalMouse& mouseClick);
    };
}