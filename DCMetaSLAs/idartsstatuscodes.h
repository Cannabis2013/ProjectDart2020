#ifndef IDARTSSTATUSCODES_H
#define IDARTSSTATUSCODES_H

class IDartsStatusCodes
{
public:
    virtual int initialized() const = 0;
    virtual int running() const = 0;
    virtual int winnerFound() const = 0;
};
#endif // IDCSTATUSCODES_H
