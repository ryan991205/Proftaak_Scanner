#ifndef PRINTER_H
#define PRINTER_H

#include <vector>
#include <string>
#include <stdint.h>
#include <arpa/inet.h>
#include "structs/Maze.h"
#include "structs/Vect.h"
#include "structs/Point.h"

#define MAX_SIZE 100

class Printer
{
    public:
        Printer(std::string ip, std::string name, uint64_t sleepMillis, int socketDescriptor);
        ~Printer();

        const std::string GetIp() { return IP; };
        const std::string GetName() { return name; };
        uint16_t GetNrOfJobs() { return nrOfJobs; };
        bool GetAlive() { return alive; };
        int GetSockDesc() {return socketDescriptor;};
        void SetSockSec(int desc) {socketDescriptor = desc;};

        //void SendJob(Maze maze);    
        void Loop();

    private:
        int socketDescriptor;
        std::vector<std::string> messageBuffer;
        std::string IP;
        std::string name;
        uint16_t nrOfJobs;
        bool alive;
        uint64_t sleepMillis;
        char message[MAX_SIZE];
        char receiveBuf[MAX_SIZE];

        void RequestNrOfJobs();
        bool HandleMessages();
};

#endif