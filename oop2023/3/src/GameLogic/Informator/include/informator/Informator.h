#pragma once

#include "enviroment/Database.h"

namespace GameLogic {
    class Informator {
    public:
        void updateInfo(const Database&) const;
    };
}