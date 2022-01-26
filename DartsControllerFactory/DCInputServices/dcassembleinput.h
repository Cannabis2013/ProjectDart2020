#ifndef DCASSEMBLEINPUT_H
#define DCASSEMBLEINPUT_H
#include "DCInputSLAs/idcassembleinput.h"
class DCServices;
struct DCPlayer;
struct DCMeta;
struct DCIndex;
class DCAssembleInput : public IDCAssembleInput
{
public:
    DCAssembleInput(DCServices *services);
    DCInput assemble(const QByteArray &byteArray) const;
private:
    void addDetails(DCInput &input, const DCIndex &index, const DCMeta &meta, const DCPlayer &player) const;
    DCServices *_services;
};

#endif // DCASSEMBLEINPUT_H
