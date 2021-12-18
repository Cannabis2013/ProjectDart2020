#ifndef IDARTSIDXBUILDER_H
#define IDARTSIDXBUILDER_H
template<typename TIndex, typename TFunctor>
class IDartsIdxBuilder
{
public:
    typedef TIndex Index;
    typedef TFunctor Functor;
    virtual Index *create(const Functor &functor) const = 0;
};
#endif // IDARTSIDXBUILDER_H
