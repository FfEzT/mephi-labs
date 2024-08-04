#pragma once

#include "ISubject.h"

namespace GameLogic {
    namespace subject {
        template <typename Parent = ISubject>
        class BasicSubject : public Parent
        {
        public:
            BasicSubject(std::unique_ptr<object::IObject> object)
                : object_( std::move(object) )
            {}

            object::IObject& getObject() override
            {
                return *object_;
            }

            const object::IObject& getObject() const override
            {
                return *object_;
            }

        private:
            std::unique_ptr<object::IObject> object_;
        };
    }
}