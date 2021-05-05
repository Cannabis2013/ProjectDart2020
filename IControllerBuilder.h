#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,
         class TModelsContextInterface,
         class TApplicatonInterface,
         class TParameterFormat>
class IControllerBuilder
{
public:
    virtual TControllerInterface *assembleDartsGameController(const TParameterFormat&,
                                                            TApplicatonInterface*,
                                                            TModelsContextInterface*) = 0;
};

#endif // ICONTROLLERBUILDER_H
