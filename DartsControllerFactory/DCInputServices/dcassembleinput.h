#ifndef DCASSEMBLEINPUT_H
#define DCASSEMBLEINPUT_H
#include "DCInputSLAs/idcbytearraytoinput.h"
class DCServices;
struct DCPlayer;
struct DCMeta;
struct DCIndex;
class DCAssembleInput : public IDCByteArrayToInput
{
public:
    DCAssembleInput(DCServices *services);
    DCInput convert(const QByteArray &byteArray) const;
private:
    void addDetails(DCInput &input, const DCIndex &index, const DCMeta &meta, const DCPlayer &player) const;
    DCServices *_services;
};

#endif // DCASSEMBLEINPUT_H
