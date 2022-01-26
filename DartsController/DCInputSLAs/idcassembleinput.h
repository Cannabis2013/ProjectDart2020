#ifndef IDCASSEMBLEINPUT_H
#define IDCASSEMBLEINPUT_H
struct DCInput;
class QByteArray;
class IDCAssembleInput
{
public:
    virtual DCInput assemble(const QByteArray &byteArray) const = 0;
};
#endif // IDCASSEMBLEINPUT_H
