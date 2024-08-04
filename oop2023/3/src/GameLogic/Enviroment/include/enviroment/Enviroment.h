#pragma once

#include <vector>
#include <memory>

#include "subject/ISubject.h"
#include "coord/Coords.h"
#include "mover/Mover.h"
#include "informator/Informator.h"
#include "engine/IEngine.h"

namespace GameLogic {
    using subject::IMoveable;
    using namespace engine;

    using std::unique_ptr;

    class Enviroment {
    public:

        Enviroment(unsigned xSize, unsigned ySize, std::unique_ptr<engine::IEngine> engine);

        const Coords& getSize() const;

        void doTick();

        const Database& getDatabase() const;
        Database& getDatabase();

        const IEngine& getEngine() const;
        IEngine& getEngine();

        bool addSubject(shared_ptr<ISubject> subject, Coords position);

        void sendRobotToInterest(const Coords& dist);

    private:
        Coords size_;

        Database data;

        unique_ptr<IEngine> engine_;
        Informator informator_;
        Mover mover_;
    };
}