#pragma once

#include "object/IObject.h"

namespace GameLogic {
    namespace subject {
        class ISubject
        {
        public:
            virtual ~ISubject() = default;

            virtual object::IObject& getObject() = 0;

            virtual const object::IObject& getObject() const = 0;
        };
    }
}