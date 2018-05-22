#include "Printer.h"

#include <unistd.h>


Printer::Printer(std::string ip, std::string name, uint64_t sleepMillis)
{
    this->ip = ip;
    this->name = name;
    nrOfJobs = 0;
    alive = true;
    this->sleepMillis = sleepMillis;

    // Start Loop on seperate thread
}

Printer::~Printer()
{
    // stop Loop
}

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

}
// post: send request to printer, used as heartbeat

bool Printer::HandleMessages()
{

    return false;
}
// post: reads messagebuffer and execute proper code, returns false if there are no messages or no proper messages