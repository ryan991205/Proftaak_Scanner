#include "Broadcaster.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>

#define port 1080

void Broadcaster::SetIP(char *IP)
{
	this->IP = IP;
}

int Broadcaster::SetUp()
{
	host = gethostbyname(IP);
	if (host == NULL)
	{
		return -1;
	}

	hostAddress.sin_family = host->h_addrtype;
	memcpy((char *)&hostAddress.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
	hostAddress.sin_port = htons(port);

	return 1;
}

int Broadcaster::Bind()
{
	printerAddress.sin_family = AF_INET;
	printerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	printerAddress.sin_port = htons(0);

	if (bind(socketDescriptor, (struct sockaddr *)&printerAddress, sizeof(printerAddress)) < 0)
	{
		close(socketDescriptor);
		return -1;
	}
	return 1;
}

int Broadcaster::Broadcast() //Let op dit is niet de constructor. Die staat onderaan.
{
	if (sendto(socketDescriptor, Message, buffersize, 0, (struct sockaddr *)&hostAddress, sizeof(hostAddress)))
	{
		close(socketDescriptor);
		return -1;
	}
	return 1;
}

Broadcaster::Broadcaster()
{
	strncpy(Message, "Who is here?", buffersize - 1); //laatste vrijhouden voor nullterminator
	Message[buffersize - 1] = '\0';
	broadcast = 1;

	if (SetUp() == -1 || Bind() == -1 || Broadcast() == -1)
	{
		perror("The setup/Bind went wrong: ");
	}

}

Broadcaster::~Broadcaster()
{
	delete IP;
	IP = NULL;
}
