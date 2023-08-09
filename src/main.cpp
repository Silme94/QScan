#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include "command.hpp"


int main(int argc, char** argv) {

    auto start = std::chrono::high_resolution_clock::now();

    char* IP = "";
    int TARGET_PORT = 0;
    int MAX_RANGE = 0;
    int THREAD_NUMBER = 10;

    if (argc <= 1) {
        COMMAND::help();
        exit(EXIT_SUCCESS);
    }

    if (strcmp(argv[1], "-h") == 0) {
        COMMAND::help();
        exit(EXIT_SUCCESS);
    }

    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            IP = argv[i + 1];
        }
        else if (strcmp(argv[i], "-p") == 0) {
            TARGET_PORT = std::stoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-m") == 0) {
            MAX_RANGE = std::stoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-t") == 0) {
            THREAD_NUMBER = std::stoi(argv[i + 1]);
        }
        else {
            if (argv[i][0] == '-') {
                std::cout << "Unknown flag: " << argv[i] << "\n";
                exit(EXIT_FAILURE);
            }
        }
    }

    if (strcmp(IP, "") == 0) {
        std::cout << "No target specified. Use '-i' to specify a target.\n";
        exit(EXIT_FAILURE);
    }

    if (TARGET_PORT != 0 && MAX_RANGE != 0) {
        std::cout << "Cannont use '-m' and '-p' at the same time.\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Starting QScan...\n";

    COMMAND::start_scan(IP, TARGET_PORT, THREAD_NUMBER, MAX_RANGE);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    auto timeDuration = duration.count();

    std::cout << "Executuion time : " << timeDuration << "s\n";

    return 0;
}
