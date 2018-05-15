#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <arpa/inet.h>

#define buffersize 10

class Broadcaster
{
  public:
    Broadcaster();
    void SetIP(char *IP);
    void Broadcast();

  private:
    int sockDescriptor;
    bool loopContinue;
    char Message[buffersize];

    struct sockaddr_in printerAddress;
    struct sockaddr_in hostAddress;
    struct hostent *host;
    int broadcast;
};

#endif