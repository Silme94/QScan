#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include "command.hpp"
#include "scanner.hpp"


namespace COMMAND {
	void help(void) noexcept {
        std::cout << "QScan - User Manual\n\n";

        // Description
        std::cout << "Description:\n";
        std::cout << "QScan is a command-line tool that allows you to scan the ports of a specified IP address to determine which ports are open and available for communication.\n\n";

        // Usage
        std::cout << "Usage:\n";
        std::cout << "QScan i- <IP>\n\n";

        // Options
        std::cout << "Options:\n";
        std::cout << " -i <IP>           The IP address of the target to scan. REQUIRED.\n";
        std::cout << " -p <PORT>         Scan only one specified port and return if the port is open or not.\n";
        std::cout << " -m <MAX_RANGE>    Set the max range ports to scan. Cannot be used with '-p' flag. DEFAULT : 65535. RECOMMANDED : 10000.\n";
        std::cout << " -t <THREAD>       Set thread numbers. DEFAULT : 10.\n\n";

        // Usage Examples
        std::cout << "Usage Examples:\n";
        std::cout << "  QScan -i 192.168.0.1   Scan the ports of the IP address 192.168.0.1.\n\n";

        // Tips
        std::cout << "Tips:\n";
        std::cout << "- Use the IP address of a remote machine that you have permission to scan.\n";
        std::cout << "- The scan results indicate open ports but do not provide information about the services that may be running on those ports.\n";
        std::cout << "- Make sure you have the necessary privileges to perform a port scan.\n\n";

        // Disclaimer
        std::cout << "Disclaimer:\n";
        std::cout << "Misusing this scanner to attempt unauthorized access to systems or networks is strictly prohibited. Be sure to use this tool ethically and responsibly, adhering to all applicable laws and regulations.\n\n";

        // Author
        std::cout << "Author:\n";
        std::cout << "[https://github.com/Silme94]\n";
	}


    void start_scan(const char* IP, int TARGET_PORT, int THREAD_NUMBER, int MAX_RANGE) {

        std::ifstream data_service("ports_services.txt");

        if (!data_service.is_open()) {
            std::cout << "Cannot open 'ports_services.txt'.\n";
            exit(EXIT_FAILURE);
        }

        std::map<int, std::string> services;

        while (data_service) {
            int port;
            char colon;
            std::string service;

            data_service >> port >> colon;
            std::getline(data_service, service);
            services[port] = service;
        }

        data_service.close();

        if (TARGET_PORT != NULL) {
            if (SCANNER::scan(IP, TARGET_PORT) == SCANNER::SCAN_SUCCESS) {
                std::string service = " UNKNOWN";

                auto it = services.find(TARGET_PORT);
                if (it != services.end()) {
                    service = it->second;
                }
                std::cout << "PORT : " << TARGET_PORT << "\nSTATE : OPEN" << "\nSERVICE :" << service << "\n";
            }
            else {
                std::cout << "PORT : " << TARGET_PORT << "\nSTATE : CLOSED\n";
            }
            return;
        }

        std::vector<std::thread> threads;
        std::vector<int> ports;
        int port = 1;
        int range = MAX_PORT_NUMBER;
        if (MAX_RANGE != 0) {
            range = MAX_RANGE;
        }

        while (port <= range) {
            for (int i = 0; i < THREAD_NUMBER && port <= range; ++i) {
                threads.emplace_back([IP, port, &ports]() {
                    SCANNER::VALID res = SCANNER::scan(IP, port);
                    printf("SCANNING PORT : %d\r", port);

                    if (res == SCANNER::SCAN_SUCCESS) {
                        ports.push_back(port);
                    }
                    });
                ++port;
            }

            for (std::thread& thread : threads) {
                thread.join();
            }

            threads.clear();
        }

        std::cout << "\nLoading...\n";
        std::cout << "\n\n";

        for (int port : ports) {
            std::string service = " UNKNOWN"; 

            auto it = services.find(port);
            if (it != services.end()) {
                service = it->second;
            }

            std::cout << "PORT : " << port << "\nSTATE : OPEN" << "\nSERVICE :" << service << "\n\n";
        }
        ports.clear();
    }

}