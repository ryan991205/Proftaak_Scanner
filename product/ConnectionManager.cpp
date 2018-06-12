#include "ConnectionManager.h"
#include "Printer.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define structSize sizeof(struct sockaddr_in)

void ConnectionManager::AcceptConnection()
{
    //accept connection from an incoming client
    clientSocket = accept(socketDescriptor, (struct sockaddr *)&client, (socklen_t *)structSize);
    processID = fork();

    if (clientSocket < 0 && processID < 0)
    {
        return;
    }

    if (processID == 0)
    {
        // nieuwe client gevonden! maak hem aan
        Printer printer(inet_ntoa (client.sin_addr), "Printer", printerSleepMillis, socketDescriptor);
        printers.push_back(printer);
        // processID == 0: child process
        printer.Loop();
        exit(0); /* Child process terminates */
    }
    else
    {
        // processID > 0: main process
        std::cout << "main waiting..." << getpid() << std::endl;
        sleep(2);
    }
    close(clientSocket);
    close(socketDescriptor);
    return;

}

int ConnectionManager::CreateSocket()
{
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        return -1;
    }

    struct timeval tv;
    tv.tv_sec = timeOut;
    tv.tv_usec = 10;



    if (0 > setsockopt(socketDescriptor, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
    {
        perror("SetSockOpt Failed: ");
        return -1;
    }

    //struct inaddr is ip, htons is port.
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(20);

    return 1;
}

int ConnectionManager::Bind()
{
    if (bind(socketDescriptor, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        return -1;
    }
    return 1;
}

void ConnectionManager::Listen()
{
    listen(socketDescriptor, 3);
}

ConnectionManager::ConnectionManager(uint64_t sleepMillis, uint64_t printerSleepMillis)
{
    CreateSocket(); //Maak een socket aan (socket_desc)
    this->sleepMillis = sleepMillis;
    this->printerSleepMillis = printerSleepMillis;

    // multithread loop function | The fuck is dit
}

void ConnectionManager::Loop() //per loop nieuwe fork. Connections refreshen
{
    bool loopContinue = true;
    while (loopContinue)
    {
        broadcaster.Broadcast();
        AcceptConnection(); //timer toevoegen

        RemoveDeadConnections();
    }

    close(socketDescriptor);
    close(clientSocket);
}

void ConnectionManager::HandleMessages()
{
    while ((read_size = recv(clientSocket, client_message, 2000, 0)) > 0)
    {
        client_message[read_size] = '\0';
        write(clientSocket, client_message, strlen(client_message));
        std::cout << client_message << std::endl;
    }

    if (read_size == 0)
    {
        std::cout << "Client disconnected" << std::endl; //moet weg
    }

    else if (read_size == -1)
    {
        std::cout << "recv failed" << std::endl; // moet weg
    }
}
// post: reads messagebuffer and execute proper code

void ConnectionManager::AddPrinter(Printer printer) //check of printer bestaat, zo niet dan voeg hem toe.
{
    if (FindPrinter(printer.GetIp()) == NULL)
    {
        printers.push_back(printer);
    }
}

Printer *ConnectionManager::FindPrinter(std::string ip) //het zoeken van een printer met een bepaald ip adres.
{
    for (uint32_t i = 0; i < printers.size(); i++)
    {
        if (printers[i].GetIp() == ip)
        {
            return &printers[i];
        }
    }
    return NULL;
}

void ConnectionManager::RemoveDeadConnections() //Loopen door alle printers, als printer bool false is, verwijder printer uit lijst.
{
    for (uint32_t i = 0; i < printers.size(); i++)
    {
        if (printers[i].GetAlive() == false)
        {
            printers.erase(printers.begin() + i);
        }
    }
}