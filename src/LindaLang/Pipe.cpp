#include <limits.h>
#include "Pipe.h"


const int Pipe::endClosed = 1;

Pipe::Pipe()
{
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
    closePipeEnd(PipeEnd::ReadEnd);
    closePipeEnd(PipeEnd::WriteEnd);
}

int Pipe::closePipeEnd(PipeEnd pe)
{
    if(pipeDescriptors[pe] != endClosed)
    {
        close(pipeDescriptors[pe]);
        pipeDescriptors[pe] = endClosed;
    }
}

void Pipe::writePipe(const void *buf, unsigned int len)
{
    if(len > PIPE_BUF)
        throw std::string("Too big message: " + len);

    if(write(pipeDescriptors[PipeEnd::WriteEnd], buf, len) == -1)
        throw std::string("Error at writing pipe");
}

bool Pipe::readPipe(void *buf, unsigned int len)
{
    int result;
    unsigned remaining = len;

    do
    {
        result = read(pipeDescriptors[PipeEnd::ReadEnd], buf, len);

        if(result == -1)
            throw std::string("Error at reading pipe");
        else if(result == 0)
        {
            if(remaining == len)
            {
                closePipeEnd(PipeEnd::ReadEnd);
                return false;
            }
            else
                throw std::string("Incomplete reading pipe");
        }

        remaining -= result;

    } while( remaining > 0);

    return true;
}



