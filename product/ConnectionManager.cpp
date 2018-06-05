#include "ConnectionManager.h"

#include "Printer.h"


#include <iostream>
#include <string.h>
#include <unistd.h>

void ConnectionManager::AcceptConnection()
{
        //comment voor saus
        c = sizeof(struct solckaddr_in);

        //accept connection from an incoming client
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
        processID = fork();

        if (client_sock < 0 && processID < 0)
        {
            return ;
        }

        if (processID == 0)
        {
            // nieuwe client gevonden! maak hem aan
            Printer printer = new Printer(inet_ntoa (client.sin_addr), "Printer", printerSleepMillis);
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
    }
    close(client_sock);
    close(socket_desc);
    return;
}

int ConnectionManager::CreateSocket()
{
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); // list met meerdere sockets voor meerdere connecties?
    if (socket_desc == -1)
    {
        return -1;
    }

    struct timeval tv =
        {
            .tv_sec = timeOut,
            .tv_usec = 10,
        };

    if (0 > setsockopt(socket_desc, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
    {
        std::cout << "setsockopt failed" << std::endl;
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
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        return -1;
    }
    return 1;
}

int ConnectionManager::Listen()
{
    listen(socket_desc, 3);
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

    close(socket_desc);
    close(client_sock);
}

void ConnectionManager::HandleMessages()
{
    while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0)
    {
        std::cout << read_size << std::endl;
        client_message[read_size] = '\0';
        write(client_sock, client_message, strlen(client_message));
        std::cout << client_message << std::endl;
    }

    if (read_size == 0)
    {
        std::cout << "Client disconnected" << std::endl;
    }

    else if (read_size == -1)
    {
        std::cout << "recv failed" << std::endl;
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