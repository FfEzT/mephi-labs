#pragma once

namespace GameLogic {
    /**
     * @brief Object-related functionality and constants.
     */
    namespace object {

        /**
         * @brief Constant representing no object.
         */
        constexpr size_t NO_OBJECT = 0;

        /**
         * @brief Constant representing a point of interest object.
         */
        constexpr size_t POINT_INTEREST = 1;

        /**
         * @brief Constant representing a let object.
         */
        constexpr size_t LET = 2;

        /**
         * @brief Constant representing a platform object.
         */
        constexpr size_t PLATFORM = 3;

        /**
         * @brief Constant representing a command platform object.
         */
        constexpr size_t COMMAND_PLATFORM = 4;
    }
}
