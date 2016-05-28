#ifndef UXP1A_PIPE_H
#define UXP1A_PIPE_H

#include <unistd.h>
#include <stdio.h>
#include <string>
#include <sys/param.h>

/**
 * Klasa reprezentująca potok nienazwany.
 */

enum PipeEnd
{
    ReadEnd = 0,
    WriteEnd = 1
};


class Pipe
{
private:

    static const int endClosed;

    int pipeDescriptors[2];

public:
    Pipe();

    Pipe(int readDescr, int writeDescr);

    ~Pipe();

    int closePipeEnd(PipeEnd pe);

    void writePipe(const void* buf, unsigned int len);

    bool readPipe(void* buf, unsigned int len);
};


#endif //UXP1A_PIPE_H
