#ifndef ABSTRACTMODELSBUILDER_H
#define ABSTRACTMODELSBUILDER_H

template<typename TModelsServiceInterface>
class AbstractModelsServiceBuilder
{
public:
    virtual TModelsServiceInterface* createLocalModelsServiceWithJsonDb() = 0;
};

#endif // ABSTRACTMODELSBUILDER_H
