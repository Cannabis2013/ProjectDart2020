#ifndef IGETDATAFROMDARTSTOURNAMENT_H
#define IGETDATAFROMDARTSTOURNAMENT_H

template<typename TTournament>
class IGetDataFromDartsTournament
{
public:
    virtual int inputHint(const TTournament* tournament) const = 0;
};

#endif // IGETDATAFROMDARTSTOURNAMENT_H
