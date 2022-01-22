#ifndef IDARTSSETIPTHINT_H
#define IDARTSSETIPTHINT_H

template<typename T,typename U,typename V>
class IGetInputs;
template<typename T>
class QVector;
template<typename TModel, typename TIndex, typename TMeta>
class IDartsSetIptHint
{
public:
    typedef TModel Model;
    typedef QVector<Model*> Models;
    typedef TIndex Index;
    typedef TMeta Meta;
    typedef IGetInputs<Model,Index,Meta> GetInputs;
    virtual void setHidden(Index *index, const Meta &meta, const Models &models, GetInputs *getInputs) const = 0;
    virtual void setVisible(Index *index, const Meta &meta, const Models &models, GetInputs *getInputs) const = 0;
};

#endif // IDARTSSETIPTHINT_H
