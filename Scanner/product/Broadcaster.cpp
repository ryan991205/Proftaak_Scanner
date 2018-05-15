#include "Broadcaster.h"

//#include <unistd.h>
void Broadcaster::SetIp(char * IP)
{
	remote_addr = IP;
}

Broadcaster::Broadcaster()
{
    strncpy(MESSAGEBUF, "Who is here?", bufferSize - 1); //laatste vrijhouden voor nullterminator
	Message[bufferSize - 1] = '\0';
	broadcast = 1;
}

void Broadcaster::Broadcast()
{

}