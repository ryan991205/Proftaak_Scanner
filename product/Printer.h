#ifndef PRINTER_H
#define PRINTER_H

#include <vector>
#include <string>
#include <stdint.h>

#include "structs/Maze.h"
#include "structs/Vect.h"
#include "structs/Point.h"

#define MAX_SIZE 100

class Printer
{
    public:
        Printer(std::string ip, std::string name, uint64_t sleepMillis);
        ~Printer();

        const std::string GetIp() { return ip; };
        const std::string GetName() { return name; };
        uint16_t GetNrOfJobs() { return nrOfJobs; };
        bool GetAlive() { return alive; };
        int GetSockDesc() {return socket_sec;};
        void SetSockSec(int desc) {socket_desc = desc;};

        //void SendJob(Maze maze);

    private:
        int socket_desc;
        std::vector<std::string> messageBuffer;
        std::string ip;
        std::string name;
        uint16_t nrOfJobs;
        bool alive;
        uint64_t sleepMillis;
        char message[MAX_SIZE];
        char receiveBuf[MAX_SIZE];

        void Loop();
        void RequestNrOfJobs();
        bool HandleMessages();
};

#endif