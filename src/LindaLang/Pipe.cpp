#include <limits.h>
#include <stdexcept>
#include "Pipe.h"
#include <iostream>
#include<sys/ipc.h>
#include<sys/sem.h>

const int Pipe::endClosed = 1;

Pipe::Pipe(int key)
{
    sem = semget(key, 1, IPC_CREAT|0666);
    semctl(sem, 0, SETVAL, 1);
    std::cout << sem << " " << semctl(sem, 0, GETVAL) << std::endl;
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
}

void Pipe::closedDescriptors()
{
    closePipeEnd(PipeEnd::ReadEnd);
    closePipeEnd(PipeEnd::WriteEnd);
}

void Pipe::closePipeEnd(PipeEnd pe)
{
    if(pipeDescriptors[pe] != endClosed)
    {
        close(pipeDescriptors[pe]);
        pipeDescriptors[pe] = endClosed;
    }
}

void Pipe::writePipe(const void *buf, unsigned long len)
{
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
    int result;
    unsigned remaining = len;


    result = read(pipeDescriptors[PipeEnd::ReadEnd], buf, len);

    struct sembuf sops[1];
    sops[0].sem_num = 0;
    sops[0].sem_flg = 0;
    sops[0].sem_op = 1;
    semop(sem, sops, 1);

    if(result == -1)
        throw std::runtime_error("Error at reading pipe");
    else if(result == 0)
    {
        if(remaining == len)
        {
            //closePipeEnd(PipeEnd::ReadEnd);
            return false;
        }
        else {
            throw std::runtime_error("Incomplete reading pipe");
        }
    }

    remaining -= result;

    return true;
}

bool Pipe::checkReadingAvailibility(unsigned timeout)
{
    struct timeval tv;
    tv.tv_sec = timeout;

    fd_set rfds;

    FD_ZERO(&rfds);
    FD_SET(pipeDescriptors[PipeEnd::ReadEnd], &rfds);

    int ret = select(pipeDescriptors[PipeEnd::ReadEnd]+1, &rfds, nullptr, nullptr, &tv);

    if(ret == -1)
        throw std::runtime_error("Error occured while select() from pipe");
    else if(ret == 0)
        return false;   // timeout

    return true;
}





