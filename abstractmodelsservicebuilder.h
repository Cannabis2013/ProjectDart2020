#ifndef ABSTRACTMODELSBUILDER_H
#define ABSTRACTMODELSBUILDER_H

template<typename TApplicationInterface, typename TModelsServiceInterface>
class AbstractModelsServiceBuilder
{
public:
    virtual TModelsServiceInterface* buildLocalModelsServiceWithJsonDb(TApplicationInterface*) = 0;
};

#endif // ABSTRACTMODELSBUILDER_H
