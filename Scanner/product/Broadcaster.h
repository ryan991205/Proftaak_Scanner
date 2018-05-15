#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <vector>
#include <string>


class Broadcaster
{
    public:
        Broadcaster();

        std::vector<std::string> GetMessageBuffer() { return messageBuffer; };

        void Broadcast();

    private:
        std::vector<std::string> messageBuffer;
        bool loopContinue;
};

#endif