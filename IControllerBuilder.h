#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,
         class TModelsContextInterface,
         class TApplicatonInterface,
         class TParameterFormat>
class IControllerBuilder
{
public:
    virtual TControllerInterface *assembleFTPGameController(const TParameterFormat&,
                                                            TApplicatonInterface*,
                                                            TModelsContextInterface*) = 0;
};

#endif // ICONTROLLERBUILDER_H
