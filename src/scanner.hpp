#pragma once

#include <iostream>

#define MAX_PORT_NUMBER 65535

namespace SCANNER {
    enum VALID {
        SCAN_FAILURE = 0,
        SCAN_SUCCESS = 1
    };

    VALID scan(const char* IP, const int PORT);
}
