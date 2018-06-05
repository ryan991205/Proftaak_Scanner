#include "Broadcaster.h"
#include <unistd.h>
#include <errno.h>

void Broadcaster::SetIP(char *IP)
{
	remote_addr = IP;
}

int Broadcaster::SetUp()
{
	host = gethostbyname(remote_addr);
	if (host == NULL)
	{
		return -1;
	}

	remoteServAddr.sin_family = host->h_addrtype;
	memcpy((char *)&remoteServAddr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
	remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);

	return 1;
}

int Broadcaster::Bind()
{
	cliAddr.sin_family = AF_INET;
	cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cliAddr.sin_port = htons(0);

	rc = bind(sd, (struct sockaddr *)&cliAddr, sizeof(cliAddr));
	if (rc < 0)
	{
		close(sd);
		return -1;
	}
	return 1;
}

int Broadcaster::Broadcast() //Let op dit is niet de constructor. Die staat onderaan.
{
	rc = sendto(sd, MESSAGEBUF, BUFSIZO, 0, (struct sockaddr *)&remoteServAddr, sizeof(remoteServAddr));

	if (rc < 0)
	{
		close(sd);
		return -1;
	}
	return 1;
}

Broadcaster::Broadcaster()
{
	strncpy(MESSAGEBUF, "Who is here?", bufferSize - 1); //laatste vrijhouden voor nullterminator
	Message[bufferSize - 1] = '\0';
	broadcast = 1;

	if (SetUp() == -1 || Bind() == -1 || BroadCast() == -1)
	{
		perror("The setup/Bind went wrong: ");
	}

}

//format cntrl shift i