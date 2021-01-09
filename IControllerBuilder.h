#ifndef ICONTROLLERBUILDER_H
#define ICONTROLLERBUILDER_H

template<class TControllerInterface,class TMode,class TParameter>
class IControllerBuilder
{
public:
    virtual TControllerInterface *buildGameController(const TMode &mode,
                                                      const TParameter &type,
                                                      const TMode &contextMode) = 0;
};

#endif // ICONTROLLERBUILDER_H
