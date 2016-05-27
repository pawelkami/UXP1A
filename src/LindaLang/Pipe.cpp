#include "Pipe.h"

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
    Close(PipeEnd::ReadEnd);
    Close(PipeEnd::WriteEnd);
}

int Pipe::Close(PipeEnd pe)
{
    close(pipeDescriptors[pe]);
}

void Pipe::writePipe(const void *buf, unsigned int len)
{
    if(len > PIPE_BUF)
        throw ("Too big message: " + len);

    if(write(pipeDescriptors[PipeEnd::WriteEnd], buf, len) == -1)
        throw "Error at writing pipe";
}

bool Pipe::readPipe(void *buf, unsigned int len)
{
    int result;
    unsigned remaining = len;

    do
    {
        result = read(pipeDescriptors[PipeEnd::ReadEnd], buf, len);

        if(result == -1)
            throw "Error at reading pipe";
        else if(result == 0)
        {
            if(remaining == len)
            {
                Close(PipeEnd::ReadEnd);
                return false;
            }
            else
                throw "Incomplete reading pipe";
        }

        remaining -= result;

    } while( remaining > 0);

    return true;
}



