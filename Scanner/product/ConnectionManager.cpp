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
        RemoveDeadConnections();
    }
    
}

void ConnectionManager::HandleMessages()
{

}
// post: reads messagebuffer and execute proper code

void ConnectionManager::AddPrinter(Printer printer) //check of printer bestaat, zo niet dan voeg hem toe.
{
    Printer* foundPrinter = FindPrinter(printer.GetIp());

    if(foundPrinter == NULL)
    {
        printers.push_back(printer);
    }
}

Printer* ConnectionManager::FindPrinter(std::string ip) //het zoeken van een printer met een bepaald ip adres.
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

void ConnectionManager::RemoveDeadConnections() //Loopen door alle printers, als printer bool false is, verwijder printer uit lijst.
{
    for(uint32_t i = 0; i < printers.size(); i++)
    {
        if(printers[i].GetAlive() == false)
        {
            printers.erase(printers.begin() + i);
        }
    }
}