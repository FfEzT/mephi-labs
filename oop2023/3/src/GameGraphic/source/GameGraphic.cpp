#include <iostream>
#include <fstream>
#include <sstream>

#include "GameGraphic.h"
#include "Builder.h"

using namespace graphic;

using namespace coord;

GameGraphic::GameGraphic()
    : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME)
{
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(FPS);

    loadTextures();

    loadMap();
}

void GameGraphic::cycle()
{
    while (window.isOpen()) {
        sf::Event event;

        optionalMouse mouseCoord = std::nullopt;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (!activePlatformId)
                    continue;

                // TODO ссылки на функции
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    getActiveMoveable().setDirection(Direction(-1, 0));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    getActiveMoveable().setDirection(Direction(1, 0));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    getActiveMoveable().setDirection(Direction(0, -1));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    getActiveMoveable().setDirection(Direction(0, 1));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    getActiveMoveable().setDirection(Direction(0, -1).setSpeed(0));
                }
                // TODO delete функцию телепорта
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    //std::queue<Coords> aha;
                    //aha.emplace(1, 1);

                    //getActiveMoveable().addNextPositions(std::move(aha));

                    if (activePointInterestId)
                        env.sendRobotToInterest(
                            env.getDatabase().getCoordsById(*activePointInterestId)
                        );
                }
            }
            if (event.type == Event::MouseButtonPressed) {
                if (Mouse::isButtonPressed(Mouse::Left))
                    mouseCoord = window.mapPixelToCoords(Mouse::getPosition(window));
            }
        }
        env.doTick();
        render(mouseCoord);
    }
}

// TODO он может быть удален
IMoveable& GameGraphic::getActiveMoveable()
{
    Database& data = env.getDatabase();
    auto& ptrSubject = env.getDatabase().getSubjectById(*activePlatformId);
    auto& moveables = data.getMoveObjects();

    if (moveables.find(*activePlatformId) == moveables.end())
        throw std::out_of_range("Not Moveable subject");

    return static_cast<subject::IMoveable&>(*ptrSubject.get());
}

void GameGraphic::loadMap() {
    Builder builder;

    std::ifstream file(MAP_PATH_FILE);
    std::string line;

    unsigned y = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        for (unsigned x = 0; x < COUNT_X_POSITION; ++x) {
            unsigned type;
            if (iss >> type) {
                Coords position(x, y);

                // TODO rewrite with vector
                switch (static_cast<ObjectType>(type)) {
                case ObjectType::LET:
                    env.addSubject(
                        builder.createLet(), position
                    );
                    break;

                case ObjectType::INTEREST:
                    env.addSubject(
                        builder.createInterest(), position
                    );
                    break;

                case ObjectType::COMMAND_CENTER:
                    env.addSubject(
                        builder.createStaticCommandPlatform(), position
                    );
                    break;

                case ObjectType::COMMAND_ROBOT:
                    env.addSubject(
                        builder.createMoveCommandPlatform(), position
                    );
                    break;

                case ObjectType::CENTER:
                    env.addSubject(
                        builder.createStaticPlatform(), position
                    );
                    break;

                case ObjectType::SCOUT:
                    env.addSubject(
                        builder.createMovePlatform(), position
                    );
                    break;
                }
            }
            else {
                // TODO except (свой тип)
                throw std::invalid_argument("в какой клетке");
            }
        }

        ++y;
    }

}

void GameGraphic::loadTextures()
{
    commandModuleTexture.loadFromFile("materials/picture/commandModule.png");
    generatorTexture.loadFromFile("materials/picture/generator.png");
    sensorTexture.loadFromFile("materials/picture/sensor.png");
    gridTexture.loadFromFile("materials/picture/grid.png");

    load_object_textures: {
        Texture NO_OBJECT;
        Texture POINT_INTEREST;
        Texture LET;
        Texture PLATFORM;
        Texture COMMAND_PLATFORM;

        NO_OBJECT.loadFromFile("materials/picture/No object.png");
        POINT_INTEREST.loadFromFile("materials/picture/Interest.png");
        LET.loadFromFile("materials/picture/Let.png");
        PLATFORM.loadFromFile("materials/picture/Platform.png");
        COMMAND_PLATFORM.loadFromFile("materials/picture/Command Platform.png");

        mapTextures.emplace(object::NO_OBJECT, std::move(NO_OBJECT));
        mapTextures.emplace(object::POINT_INTEREST, std::move(POINT_INTEREST));
        mapTextures.emplace(object::LET, std::move(LET));
        mapTextures.emplace(object::PLATFORM, std::move(PLATFORM));
        mapTextures.emplace(object::COMMAND_PLATFORM, std::move(COMMAND_PLATFORM));
    }
}


void GameGraphic::render(optionalMouse& mouseClick)
{
    Clock clock;
    clock.restart();

    window.clear();

    drawHeader();
    drawFooter();
    drawGrid();
    drawObjects(mouseClick);

    window.display();

    if constexpr (DEBUG_FPS)
        std::cout << clock.getElapsedTime().asMilliseconds() << '\n';
}

// TODO
void GameGraphic::drawHeader()
{}

void GameGraphic::drawFooter()
{
    sf::RectangleShape main(Vector2f(WINDOW_WIDTH, FOOTER_HEIGHT));
    main.setPosition(0, WINDOW_HEIGHT);
    main.setOrigin(0, FOOTER_HEIGHT);
    main.setFillColor(INTERFACE_COLOR);
    window.draw(main);

    Sprite sensor(sensorTexture);
    sensor.setOrigin(0, FOOTER_HEIGHT);
    sensor.setPosition(0, WINDOW_HEIGHT);
    window.draw(sensor);

    Sprite generator(generatorTexture);
    generator.setOrigin(0, FOOTER_HEIGHT);
    generator.setPosition(FOOTER_SIZE_ONE_BLOCK, WINDOW_HEIGHT);
    window.draw(generator);

    Sprite command(commandModuleTexture);
    command.setOrigin(0, FOOTER_SIZE_ONE_BLOCK);
    command.setPosition(0, WINDOW_HEIGHT);
    window.draw(command);
}

void GameGraphic::drawGrid()
{
    Sprite grid(gridTexture);
    grid.setPosition(0, HEADER_HEIGHT - FIX);
    window.draw(grid);
}

void GameGraphic::drawObjects(optionalMouse& mouseClick)
{
    const Database& data = env.getDatabase();

    for (const auto& obj : data.getIdToCoord()) {
        Sprite objectGraphic;
        // TODO config 5, 5
        objectGraphic.setOrigin(5, 5);
        objectGraphic.setScale(SIZE_ONE_BLOCK / SIZE_TEXTURE_BLOCK_PX, SIZE_ONE_BLOCK / SIZE_TEXTURE_BLOCK_PX);

        const IObject& ptr = data.getSubjectById(obj.first)->getObject();

        objectGraphic.setTexture(mapTextures[ptr.getIdTexture()]);

        const Coords& position = obj.second;
        objectGraphic.setPosition(position.x * SIZE_ONE_BLOCK, HEADER_HEIGHT + position.y * SIZE_ONE_BLOCK);

        if (mouseClick && objectGraphic.getGlobalBounds().contains(mouseClick->x, mouseClick->y)) {
            if (dynamic_cast<const Platform*>(&ptr)) {
                //auto& platform = static_cast<object::Platform&>(ptr);

                // TODO
                //if (platform.isActive() && platform.isUnderControl())
                activePlatformId = obj.first;

            }
            if (dynamic_cast<const IPointInterest*>(&ptr)) {
                activePointInterestId = obj.first;
            }

            if (activePlatformId && DEBUG_ACTIVE_ID) {
                std::cout << "Active id: " << *activePlatformId << '\n';
                std::cout << "Coords: " << position.x << ' ' << position.y << '\n';
            }
        }

        window.draw(objectGraphic);
    }
}
