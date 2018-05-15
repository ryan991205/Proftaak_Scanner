#include "ConnectionManager.h"

#include <unistd.h>


ConnectionManager::ConnectionManager(uint64_t sleepMillis, uint64_t printerSleepMillis)
{
    this->sleepMillis = sleepMillis;
    this->printerSleepMillis = printerSleepMillis;

    // multithread loop function
}

void ConnectionManager::Loop()
{
    bool loopContinue = true;
    while(loopContinue)
    {
        broadcaster.Broadcast();
        usleep(sleepMillis);
        HandleMessages();
    }
}

void ConnectionManager::HandleMessages()
{

}
// post: reads messagebuffer and execute proper code

void ConnectionManager::AddPrinter(Printer printer)
{
    Printer* foundPrinter = FindPrinter(printer.GetIp());

    if(foundPrinter == NULL)
    {
        printers.push_back(printer);
    }
}

Printer* ConnectionManager::FindPrinter(std::string ip)
{
    for(uint32_t i = 0; i < printers.size(); i++)
    {
        if(printers[i].GetIp() == ip)
        {
            return &printers[i];
        }
    }

    return NULL;
}

void ConnectionManager::RemoveDeadConnections()
{
    for(uint32_t i = 0; i < printers.size(); i++)
    {
        if(printers[i].GetAlive() == false)
        {
            printers.erase(printers.begin() + i);
        }
    }
}