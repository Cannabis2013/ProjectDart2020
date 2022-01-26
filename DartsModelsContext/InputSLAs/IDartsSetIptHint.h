#ifndef IDARTSSETIPTHINT_H
#define IDARTSSETIPTHINT_H

template<typename T,typename U,typename V>
class IGetInputs;
template<typename T>
class QVector;
template<typename TInput, typename TIndex, typename TMeta>
class IDartsSetIptHint
{
public:
    typedef TInput Input;
    typedef QVector<Input*> Inputs;
    typedef TIndex Index;
    typedef TMeta Meta;
    typedef IGetInputs<Input,Index,Meta> GetInputs;
    virtual void setHidden(Index *index, const Meta &meta, const Inputs &models, GetInputs *getInputs) const = 0;
    virtual void setVisible(Index *index, const Meta &meta, const Inputs &models, GetInputs *getInputs) const = 0;
    virtual void setVisible(Input *input) const = 0;
};

#endif // IDARTSSETIPTHINT_H
