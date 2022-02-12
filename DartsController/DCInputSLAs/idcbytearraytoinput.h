#ifndef IDCBYTEARRAYTOINPUT_H
#define IDCBYTEARRAYTOINPUT_H
struct DCInput;
class QByteArray;
class IDCByteArrayToInput
{
public:
    virtual DCInput convert(const QByteArray &byteArray) const = 0;
};
#endif // IDCASSEMBLEINPUT_H
