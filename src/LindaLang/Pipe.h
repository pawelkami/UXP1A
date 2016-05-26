
#ifndef UXP1A_PIPE_H
#define UXP1A_PIPE_H

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
    int pipeDescriptors[2];

public:
    void write(const void* buf, unsigned int len);

    void read(void* buf, unsigned int len);
};


#endif //UXP1A_PIPE_H
