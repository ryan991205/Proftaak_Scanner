#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <vector>
#include <string>
#include <stdint.h>
#include <arpa/inet.h> //inet_addr

#include "Printer.h"
#include "Broadcaster.h"

class ConnectionManager
{
  public:
    ConnectionManager(uint64_t sleepMillis, uint64_t printerSleepMillis);
    r > GetPrinters() { return printers; };

    Printer *FindPrinter(std::string ip);

  private:
    int socket_desc;
    int c;
    int read_size;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char client_message[2000];

    pid_t processID; /* Process ID from fork() */
    bool to_quit;
    int timeOut;

    std::vector<Printer> printers;
    Broadcaster broadcaster;
    uint64_t sleepMillis;
    uint64_t printerSleepMillis;
    int Bind();
    void Listen();
    void AcceptConnection();
    int CreateSocket();
    void Loop();
    void HandleMessages();
    void AddPrinter(Printer printer);
    void RemoveDeadConnections();
};

#endif