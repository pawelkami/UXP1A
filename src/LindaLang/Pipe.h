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

    void closePipeEnd(PipeEnd pe);

    void writePipe(const void* buf, unsigned long len);

    bool readPipe(void* buf, unsigned long len);

    /**
     * Metoda do sprawdzenia czy jest coś do przeczytania w potoku.
     */
    bool checkReadingAvailibility(unsigned timeout);
};


#endif //UXP1A_PIPE_H
