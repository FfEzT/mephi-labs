#pragma once

namespace GameLogic {

    /**
     * @brief Namespace for coordinate-related functionality.
     */
    namespace coord {

        /**
         * @brief Represents a direction in 2D space.
         */
        class Direction {
        public:
            /**
             * @brief Constructor with default values for x and y.
             * if vector (x,y) isn't normalise, constructor will be transform it to
             * normalized vector, and speed will be move to the field "speed"
             */
            Direction(int xPos = 0, int yPos = 1);

            /**
             * @brief Get the x-coordinate of the direction.
             * @return The x-coordinate.
             */
            short getX() const;

            /**
             * @brief Get the y-coordinate of the direction.
             * @return The y-coordinate.
             */
            short getY() const;

            /**
             * @brief Get the speed of the direction.
             * @return The speed.
             */
            unsigned getSpeed() const;

            /**
             * @brief Set the speed of the direction.
             * @param speed The new speed value.
             * @return Reference to the updated Direction.
             */
            Direction& setSpeed(unsigned speed);

            /**
             * @brief Overloaded addition operator for combining directions.
             * @param other The Direction to add.
             * @return A new Direction representing the sum.
             */
            Direction operator+(const Direction& other);

            bool operator==(const Direction&) const = default;

        private:
            unsigned speed; ///< Speed of the direction.
            short x;       ///< X-coordinate of the direction.
            short y;       ///< Y-coordinate of the direction.
        };
    } // namespace coord
} // namespace GameLogic
