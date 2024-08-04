#pragma once

#include "IdTexture.h"

namespace GameLogic {
    namespace object {

        /**
         * @brief Interface for game objects.
         */
        class IObject {
        public:
            /**
             * @brief Virtual destructor for interface.
             */
            virtual ~IObject() = default;

            /**
             * @brief Get the ID of the object's texture.
             * @return The ID of the texture.
             */
            virtual size_t getIdTexture() const { return NO_OBJECT; }
        };

        /**
         * @brief Interface for let objects.
         */
        class ILet : public IObject {
        public:
            /**
             * @brief Virtual destructor for interface.
             */
            virtual ~ILet() = default;

            /**
             * @brief Override to return the ID for let texture.
             * @return The ID of the let texture.
             */
            size_t getIdTexture() const override { return LET; }
        };

        /**
         * @brief Interface for point of interest objects.
         */
        class IPointInterest : public IObject {
        public:
            /**
             * @brief Virtual destructor for interface.
             */
            virtual ~IPointInterest() = default;

            /**
             * @brief Override to return the ID for point of interest texture.
             * @return The ID of the point of interest texture.
             */
            size_t getIdTexture() const override { return POINT_INTEREST; }
        };
    } // namespace object
} // namespace GameLogic
