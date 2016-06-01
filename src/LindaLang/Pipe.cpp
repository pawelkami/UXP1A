#include <limits.h>
#include <stdexcept>
#include "Pipe.h"
#include "LindaLogger.h"
#include <iostream>
#include<sys/ipc.h>
#include<sys/sem.h>

const int Pipe::endClosed = 1;

Pipe::Pipe(int key)
{
    LOG_DEBUG("key = " + std::to_string(key));
    sem = semget(key, 1, IPC_CREAT|0666);
    semctl(sem, 0, SETVAL, 1);
    if(pipe(pipeDescriptors) == -1)
        throw "";
}

Pipe::Pipe(int readDescr, int writeDescr)
{
    pipeDescriptors[PipeEnd::ReadEnd] = readDescr;
    pipeDescriptors[PipeEnd::WriteEnd] = writeDescr;
}

Pipe::~Pipe()
{
    LOG_DEBUG("");
}

void Pipe::closeDescriptors()
{
    LOG_DEBUG("");
    closePipeEnd(PipeEnd::ReadEnd);
    closePipeEnd(PipeEnd::WriteEnd);
}

void Pipe::closePipeEnd(PipeEnd pe)
{
    if(pipeDescriptors[pe] != endClosed)
    {
        LOG_INFO(pe == PipeEnd::ReadEnd ? "ReadEnd" : "WriteEnd");
        close(pipeDescriptors[pe]);
        pipeDescriptors[pe] = endClosed;
    }
}

void Pipe::writePipe(const void *buf, unsigned long len)
{
    LOG_DEBUG("");
    struct sembuf sops[1];
    sops[0].sem_num = 0;
    sops[0].sem_flg = 0;
    sops[0].sem_op = -1;
    semop(sem, sops, 1);

    if(len > PIPE_BUF)
        throw std::runtime_error("Too big message: " + std::to_string(len));

    if(write(pipeDescriptors[PipeEnd::WriteEnd], buf, len) == -1)
        throw std::runtime_error(std::strerror(errno));
}

bool Pipe::readPipe(void *buf, unsigned long len)
{
    LOG_DEBUG("");
    int result;

    result = read(pipeDescriptors[PipeEnd::ReadEnd], buf, len);

    struct sembuf sops[1];
    sops[0].sem_num = 0;
    sops[0].sem_flg = 0;
    sops[0].sem_op = 1;
    semop(sem, sops, 1);

    if(result == -1)
        throw std::runtime_error("Error at reading pipe");

    return true;
}

bool Pipe::checkReadingAvailibility(unsigned timeout)
{
    LOG_DEBUG("");
    struct timeval tv;
    tv.tv_sec = timeout;

    fd_set rfds;

    FD_ZERO(&rfds);
    FD_SET(pipeDescriptors[PipeEnd::ReadEnd], &rfds);

    int ret = select(pipeDescriptors[PipeEnd::ReadEnd]+1, &rfds, nullptr, nullptr, &tv);

    if(ret == -1)
        throw std::runtime_error("Error occured while select() from pipe");
    else if(ret == 0)
    {
        LOG_INFO("Timeout occurred");
        return false;   // timeout
    }

    return true;
}

Pipe::Pipe()
{

}







