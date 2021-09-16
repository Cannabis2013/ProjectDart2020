#ifndef IDARTSSUGGESTIONVALUES_H
#define IDARTSSUGGESTIONVALUES_H

class IDartsAttemptValues
{
public:
    virtual int attempts() const = 0;
    virtual int lastAttemptKeyCode() const = 0;
};
#endif // IDARTSKEYMETAVALUES_H
