#include "../inc/TCPserver.hpp"
#include "../inc/TCPsocket.hpp"
#include "../inc/include.hpp"
#include "../inc/utils.hpp"

bool run = true;
void sigintHandler(int) {
    std::cout << "\n" + displayTimestamp() + "-!- [SERVER] Shutting down server..." << std::endl;
    run = false;
}

/*
** args: av[1] = port
**       av[2] = password
*/
int main(int ac, char* av[]) {

    if (ac != 3 || !portIsValid(av[1])) {
        std::cout << "Usage: ./server <port> <password>" << std::endl;
        return EXIT_FAILURE;
    }

    signal(SIGINT, sigintHandler);
    signal(SIGTERM, sigintHandler);
    signal(SIGQUIT, sigintHandler);

RETRY:
    try {
        TCPserver server(std::atoi(av[1]), av[2]);
        while (run)
            server.runServer();
    } catch (std::exception& e) {
        std::cout << displayTimestamp() << "-!- [FATAL] " << e.what() << std::endl;
        std::cout << displayTimestamp() << "-!- [SERVER] Retrying in 3 seconds..." << std::endl;
        sleep(3);
        goto RETRY;
    }

    return EXIT_SUCCESS;
}

/*
** SOURCES:
** https://www.man7.org/linux/man-pages/man2/poll.2.html
** https://www.ibm.com/docs/en/i/7.3?topic=designs-using-poll-instead-select
*/