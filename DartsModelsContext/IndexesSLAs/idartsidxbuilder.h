#ifndef IDARTSIDXBUILDER_H
#define IDARTSIDXBUILDER_H
class QByteArray;
template<typename TIndex>
class IDartsIdxBuilder
{
public:
    typedef TIndex Index;
    typedef QByteArray ByteArray;
    virtual Index *create(const ByteArray &byteArray) const = 0;
};
#endif // IDARTSIDXBUILDER_H
