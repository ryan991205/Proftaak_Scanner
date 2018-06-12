#include "Printer.h"

#include <unistd.h>
#include <string.h>

Printer::Printer(std::string IP, std::string name, uint64_t sleepMillis, int socketDescriptor)
{
    this->IP = IP;
    this->name = name;
    nrOfJobs = 0;
    alive = true;
    this->sleepMillis = sleepMillis;
    this->socketDescriptor = socketDescriptor;

    // Start Loop on seperate thread
    strncpy(message, "nrOfJobs", MAX_SIZE);
}

Printer::~Printer()
{
    // stop Loop
}
// kan weg
void Printer::Loop()
{
    alive = true;
    while(alive)
    {
        RequestNrOfJobs();
        usleep(sleepMillis);
        alive = HandleMessages();
    }
}

//void Printer::SendJob(Maze maze)
//{
//  
//}
// post: sends maze over TCP connection

void Printer::RequestNrOfJobs()
{
    send (socketDescriptor, message, MAX_SIZE, 0);

    if (recv (socketDescriptor, receiveBuf, MAX_SIZE, 0) < 0)
    {
        alive = false;
    }
}
// post: send request to printer, used as heartbeat

bool Printer::HandleMessages()
{
    nrOfJobs = receiveBuf[0];
    return false;
}
// post: reads messagebuffer and execute proper code, returns false if there are no messages or no proper messages