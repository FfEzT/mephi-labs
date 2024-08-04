#ifndef _utils
#define _utils

#include <iostream>

namespace utils {
    inline int getRandom() {
        static time_t prevTime = time(NULL);

        if (prevTime == time(NULL)) {
            srand(prevTime * rand());
        }
        else {
            prevTime = time(NULL);
            srand(prevTime);
        }

        return rand();
    }
}

#endif