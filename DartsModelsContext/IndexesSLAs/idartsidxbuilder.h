#ifndef IDARTSIDXBUILDER_H
#define IDARTSIDXBUILDER_H
template<typename TIndex, typename TByteArray>
class IDartsIdxBuilder
{
public:
    typedef TIndex Index;
    typedef TByteArray ByteArray;
    virtual Index *create(const ByteArray &byteArray) const = 0;
};
#endif // IDARTSIDXBUILDER_H
