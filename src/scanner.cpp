#include "scanner.hpp"
#include <iostream>
#include <winsock2.h>


namespace SCANNER {

    VALID scan(const char* IP, const int PORT) {
        WSADATA wsa;
        struct sockaddr_in sockaddr;
        SOCKET sock;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            return SCAN_FAILURE;
        }

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            WSACleanup();
            return SCAN_FAILURE;
        }

        sockaddr.sin_addr.s_addr = inet_addr(IP);
        sockaddr.sin_port = htons(PORT);
        sockaddr.sin_family = AF_INET;

        if (connect(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR) {
            closesocket(sock);
            WSACleanup();
            return SCAN_FAILURE;
        }

        closesocket(sock);
        WSACleanup();
        return SCAN_SUCCESS;
    }
}