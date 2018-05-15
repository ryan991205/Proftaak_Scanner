#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <vector>
#include <string>
#include <stdint.h>

#include "Printer.h"
#include "Broadcaster.h"


class ConnectionManager
{
    public:
        ConnectionManager(uint64_t sleepMillis, uint64_t printerSleepMillis);
        r> GetPrinters() { return printers; };

        Printer* FindPrinter(std::string ip);

    private:
        std::vector<Printer> printers;
        Broadcaster broadcaster;
        uint64_t sleepMillis;
        uint64_t printerSleepMillis;

        void Loop();
        void HandleMessages();
        void AddPrinter(Printer printer);
        void RemoveDeadConnections();
};

#endif