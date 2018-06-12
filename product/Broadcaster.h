#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <arpa/inet.h>

#define buffersize 10

class Broadcaster
{
public:
  Broadcaster();
  ~Broadcaster();
  void SetIP(char *IP);
  int Broadcast();


private:
  int SetUp();
  int Bind();


  int socketDescriptor;
  char Message[buffersize];

  struct sockaddr_in printerAddress;
  struct sockaddr_in hostAddress;
  struct hostent *host;
  int broadcast;
  char* IP;
};

#endif